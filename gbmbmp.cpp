/*

gbmbmp.c - OS/2 1.1, 1.2, 2.0 and Windows 3.0 support

Reads and writes any OS/2 1.x bitmap.
Will also read uncompressed, RLE4 and RLE8 Windows 3.x bitmaps too.
There are horrific file structure alignment considerations hence each
word,dword is read individually.
*/

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   /*...sincludes:0:*/
   #include <stdio.h>
   #include <ctype.h>
   #include <stddef.h>
   #include <stdlib.h>
   #include <string.h>
   #include <memory.h>
   //#include <malloc.h>
   #include "gbm.h"
   #include "gbmhelp.h"
//   #include "debugheap.h"
#endif

#ifndef min
#define min(a,b)        (((a)<(b))?(a):(b))
#endif

#define low_byte(w)     ((byte)  ((w)&0x00ff)    )
#define high_byte(w)    ((byte) (((w)&0xff00)>>8))
#define make_word(a,b)  (((word)a) + (((word)b) << 8))

static BOOLEAN read_word(int fd, word *w)
{
    byte low = 0, high = 0;

    if ( gbm_file_read(fd, (char *) &low, 1) != 1 )
        return FALSE;
    if ( gbm_file_read(fd, (char *) &high, 1) != 1 )
        return FALSE;
    *w = (word) (low + ((word) high << 8));
    return TRUE;
}

static BOOLEAN read_dword(int fd, dword *d)
{
    word low, high;
    if ( !read_word(fd, &low) )
        return FALSE;
    if ( !read_word(fd, &high) )
        return FALSE;
    *d = low + ((dword) high << 16);
    return TRUE;
}

static BOOLEAN write_word(int fd, word w)
{
    byte low  = (byte) w;
    byte high = (byte) (w >> 8);

    gbm_file_write(fd, &low, 1);
    gbm_file_write(fd, &high, 1);
    return TRUE;
}

static BOOLEAN write_dword(int fd, dword d)
{
    write_word(fd, (word) d);
    write_word(fd, (word) (d >> 16));
    return TRUE;
}

static const GBMFT bmp_gbmft =
{
    L"Bitmap",
    L"OS/2 1.1, 1.2, 2.0 / Windows 3.0 bitmap",
    L"BMP VGA BGA RLE DIB RL4 RL8",
    GBM_FT_R1|GBM_FT_R4|GBM_FT_R8|GBM_FT_R24|
    GBM_FT_W1|GBM_FT_W4|GBM_FT_W8|GBM_FT_W24,
};

#define GBM_ERR_BMP_PLANES      ((GBM_ERR) 300)
#define GBM_ERR_BMP_BITCOUNT    ((GBM_ERR) 301)
#define GBM_ERR_BMP_CBFIX       ((GBM_ERR) 302)
#define GBM_ERR_BMP_COMP        ((GBM_ERR) 303)
#define GBM_ERR_BMP_OFFSET      ((GBM_ERR) 304)

typedef struct
{
    dword base;
    BOOLEAN windows;
    dword cbFix;
    dword ulCompression;
    dword cclrUsed;
    dword offBits;
    BOOLEAN inv, invb;
} BMP_PRIV;

#define BFT_BMAP        0x4d42
#define BFT_BITMAPARRAY 0x4142
#define BCA_UNCOMP      0x00000000L
#define BCA_RLE8        0x00000001L
#define BCA_RLE4        0x00000002L
#define BCA_HUFFFMAN1D  0x00000003L
#define BCA_RLE24       0x00000004L
#define MSWCC_EOL       0
#define MSWCC_EOB       1
#define MSWCC_DELTA     2

static void invert(byte *buffer, unsigned count)
{
    while ( count-- )
        *buffer++ ^= (byte) 0xffU;
}

static void swap_pal(GBMRGB *gbmrgb)
{
    GBMRGB tmp = gbmrgb[0];
    gbmrgb[0] = gbmrgb[1];
    gbmrgb[1] = tmp;
}


GBM_ERR bmp_qft(GBMFT *gbmft)
{
    *gbmft = bmp_gbmft;
    return GBM_ERR_OK;
}

GBM_ERR bmp_rhdr(const wchar_t *fn, int fd, GBM *gbm)
{
    word usType, xHotspot, yHotspot;
    dword cbSize, offBits, cbFix;
    BMP_PRIV *bmp_priv = (BMP_PRIV *) gbm->priv;
    bmp_priv->inv  = 0;
    bmp_priv->invb = 0;

    if ( !read_word(fd, &usType) )
        return GBM_ERR_READ;
    if ( usType == BFT_BITMAPARRAY )
    {
        int i = 0;

        while ( i-- > 0 )
        {
            dword cbSize2, offNext;

            if ( !read_dword(fd, &cbSize2) )
                return GBM_ERR_READ;
            if ( !read_dword(fd, &offNext) )
                return GBM_ERR_READ;
            if ( offNext == 0L )
                return GBM_ERR_BMP_OFFSET;
            gbm_file_lseek(fd, (long) offNext, SEEK_SET);
            if ( !read_word(fd, &usType) )
                return GBM_ERR_READ;
            if ( usType != BFT_BITMAPARRAY )
                return GBM_ERR_BAD_MAGIC;
        }
        gbm_file_lseek(fd, 4L + 4L + 2L + 2L, SEEK_CUR);
        if ( !read_word(fd, &usType) )
            return GBM_ERR_READ;
    }

    if ( usType != BFT_BMAP )
        return GBM_ERR_BAD_MAGIC;

    bmp_priv->base = (dword) ( gbm_file_lseek(fd, 0L, SEEK_CUR) - 2L );

    if ( !read_dword(fd, &cbSize) )
        return GBM_ERR_READ;
    if ( !read_word(fd, &xHotspot) )
        return GBM_ERR_READ;
    if ( !read_word(fd, &yHotspot) )
        return GBM_ERR_READ;
    if ( !read_dword(fd, &offBits) )
        return GBM_ERR_READ;
    if ( !read_dword(fd, &cbFix) )
        return GBM_ERR_READ;

    bmp_priv->offBits = offBits;

    if ( cbFix == 12 )
        /* OS/2 1.x uncompressed bitmap */
    {
        word cx, cy, cPlanes, cBitCount;

        if ( !read_word(fd, &cx) )
            return GBM_ERR_READ;
        if ( !read_word(fd, &cy) )
            return GBM_ERR_READ;
        if ( !read_word(fd, &cPlanes) )
            return GBM_ERR_READ;
        if ( !read_word(fd, &cBitCount) )
            return GBM_ERR_READ;

        if ( cx == 0 || cy == 0 )
            return GBM_ERR_BAD_SIZE;
        if ( cPlanes != 1 )
            return GBM_ERR_BMP_PLANES;
        if ( cBitCount != 1 && cBitCount != 4 && cBitCount != 8 && cBitCount != 24 )
            return GBM_ERR_BMP_BITCOUNT;

        gbm->w   = (int) cx;
        gbm->h   = (int) cy;
        gbm->bpp = (int) cBitCount;

        bmp_priv->windows = FALSE;
    }
    else if ( cbFix >= 16 && cbFix <= 64 &&
              ((cbFix & 3) == 0 || cbFix == 42 || cbFix == 46) )
        /* OS\2 and Windows 3.0 */
    {
        word cPlanes, cBitCount, usUnits, usReserved, usRecording, usRendering;
        dword ulWidth, ulHeight, ulCompression;
        dword ulSizeImage, ulXPelsPerMeter, ulYPelsPerMeter;
        dword cclrUsed, cclrImportant, cSize1, cSize2, ulColorEncoding, ulIdentifier;
        BOOLEAN ok;

        ok  = read_dword(fd, &ulWidth);
        ok &= read_dword(fd, &ulHeight);
        ok &= read_word(fd, &cPlanes);
        ok &= read_word(fd, &cBitCount);
        if ( cbFix > 16 )
            ok &= read_dword(fd, &ulCompression);
        else
            ulCompression = BCA_UNCOMP;
        if ( cbFix > 20 )
            ok &= read_dword(fd, &ulSizeImage);
        if ( cbFix > 24 )
            ok &= read_dword(fd, &ulXPelsPerMeter);
        if ( cbFix > 28 )
            ok &= read_dword(fd, &ulYPelsPerMeter);
        if ( cbFix > 32 )
            ok &= read_dword(fd, &cclrUsed);
        else
            cclrUsed = ( (dword)1 << cBitCount );
        if ( cBitCount != 24 && cclrUsed == 0 )
            cclrUsed = ( (dword)1 << cBitCount );

        /* Protect against badly written bitmaps! */
        if ( cclrUsed > ( (dword)1 << cBitCount ) )
            cclrUsed = ( (dword)1 << cBitCount );

        if ( cbFix > 36 )
            ok &= read_dword(fd, &cclrImportant);
        if ( cbFix > 40 )
            ok &= read_word(fd, &usUnits);
        if ( cbFix > 42 )
            ok &= read_word(fd, &usReserved);
        if ( cbFix > 44 )
            ok &= read_word(fd, &usRecording);
        if ( cbFix > 46 )
            ok &= read_word(fd, &usRendering);
        if ( cbFix > 48 )
            ok &= read_dword(fd, &cSize1);
        if ( cbFix > 52 )
            ok &= read_dword(fd, &cSize2);
        if ( cbFix > 56 )
            ok &= read_dword(fd, &ulColorEncoding);
        if ( cbFix > 60 )
            ok &= read_dword(fd, &ulIdentifier);

        if ( !ok )
            return GBM_ERR_READ;

        if ( ulWidth == 0L || ulHeight == 0L )
            return GBM_ERR_BAD_SIZE;
        if ( cPlanes != 1 )
            return GBM_ERR_BMP_PLANES;
        if ( cBitCount != 1 && cBitCount != 4 && cBitCount != 8 && cBitCount != 24 )
            return GBM_ERR_BMP_BITCOUNT;

        gbm->w   = (int) ulWidth;
        gbm->h   = (int) ulHeight;
        gbm->bpp = (int) cBitCount;

        bmp_priv->windows       = TRUE;
        bmp_priv->cbFix         = cbFix;
        bmp_priv->ulCompression = ulCompression;
        bmp_priv->cclrUsed      = cclrUsed;
    }
    else
        return GBM_ERR_BMP_CBFIX;

    return GBM_ERR_OK;
}

GBM_ERR bmp_rpal(int fd, GBM *gbm, GBMRGB *gbmrgb)
{
    BMP_PRIV *bmp_priv = (BMP_PRIV *) gbm->priv;

    if ( gbm->bpp != 24 )
    {
        int i;
        byte b[4];

        if ( bmp_priv->windows )
        {
            /* OS/2 and Windows 3.0 */
            gbm_file_lseek(fd, (long) (bmp_priv->base + 14L + bmp_priv->cbFix), SEEK_SET);
            for ( i = 0; i < (int) bmp_priv->cclrUsed; i++ )
            {
                gbm_file_read(fd, b, 4);
                gbmrgb[i].b = b[0];
                gbmrgb[i].g = b[1];
                gbmrgb[i].r = b[2];
            }
        }
        else
        {
            /* OS/2 */
            gbm_file_lseek(fd, (long) (bmp_priv->base + 26L), SEEK_SET);
            for ( i = 0; i < (1 << gbm->bpp); i++ )
            {
                gbm_file_read(fd, b, 3);
                gbmrgb[i].b = b[0];
                gbmrgb[i].g = b[1];
                gbmrgb[i].r = b[2];
            }
        }
    }

    if ( gbm->bpp == 1 && !bmp_priv->inv )
        swap_pal(gbmrgb);

    return GBM_ERR_OK;
}

GBM_ERR bmp_rdata(int fd, GBM *gbm, byte *data)
{
    BMP_PRIV *bmp_priv = (BMP_PRIV *) gbm->priv;
    int cLinesWorth = ((gbm->bpp * gbm->w + 31) / 32) * 4;

    if ( bmp_priv->windows )
    {
        /* OS/2 and Windows 3.0 */
        gbm_file_lseek(fd, (long)bmp_priv->offBits, SEEK_SET);

        switch ( (int) bmp_priv->ulCompression )
        {
        case BCA_UNCOMP:
            gbm_file_read(fd, data, gbm->h * cLinesWorth);
            break;

        case BCA_RLE8:
            {
                AHEAD *ahead;
                int x = 0, y = 0;
                BOOLEAN eof8 = FALSE;

                if ( (ahead = gbm_create_ahead(fd)) == NULL )
                    return GBM_ERR_MEM;

                while ( !eof8 )
                {
                    byte c = (byte) gbm_read_ahead(ahead);
                    byte d = (byte) gbm_read_ahead(ahead);

                    if ( c )
                    {
                        memset(data, d, c);
                        x += c;
                        data += c;
                    }
                    else
                        switch ( d )
                        {
                        case MSWCC_EOL:
                            {
                                int to_eol = cLinesWorth - x;

                                memset(data, 0, (size_t) to_eol);
                                data += to_eol;
                                x = 0;
                                if ( ++y == gbm->h )
                                    eof8 = TRUE;
                            }
                            break;

                        case MSWCC_EOB:
                            if ( y < gbm->h )
                            {
                                int to_eol = cLinesWorth - x;

                                memset(data, 0, (size_t) to_eol);
                                x = 0; y++;
                                data += to_eol;
                                while ( y < gbm->h )
                                {
                                    memset(data, 0, (size_t) cLinesWorth);
                                    data += cLinesWorth;
                                    y++;
                                }
                            }
                            eof8 = TRUE;
                            break;

                        case MSWCC_DELTA:
                            {
                                byte dx = (byte) gbm_read_ahead(ahead);
                                byte dy = (byte) gbm_read_ahead(ahead);
                                int fill = dx + dy * cLinesWorth;
                                memset(data, 0, (size_t) fill);
                                data += fill;
                                x += dx; y += dy;
                                if ( y == gbm->h )
                                    eof8 = TRUE;
                            }
                            break;

                        default:
                            {
                                int n = (int) d;

                                while ( n-- > 0 )
                                    *data++ = (byte) gbm_read_ahead(ahead);
                                x += d;
                                if ( d & 1 )
                                    gbm_read_ahead(ahead); /* Align */
                            }
                            break;
                        }
                }

                gbm_destroy_ahead(ahead);
            }
            break;

        case BCA_RLE4:
            {
                AHEAD *ahead;
                int x = 0, y = 0;
                BOOLEAN eof4 = FALSE;
                int inx = 0;

                if ( (ahead = gbm_create_ahead(fd)) == NULL )
                    return GBM_ERR_MEM;

                memset(data, 0, (size_t) (gbm->h * cLinesWorth));

                while ( !eof4 )
                {
                    byte c = (byte) gbm_read_ahead(ahead);
                    byte d = (byte) gbm_read_ahead(ahead);

                    if ( c )
                    {
                        byte h, l;
                        int i;
                        if ( x & 1 )
                        { h = (byte) (d >> 4); l = (byte) (d << 4); }
                        else
                        { h = (byte) (d&0xf0); l = (byte) (d&0x0f); }
                        for ( i = 0; i < (int) c; i++, x++ )
                        {
                            if ( x & 1U )
                                data[inx++] |= l;
                            else
                                data[inx]   |= h;
                        }
                    }
                    else
                        switch ( d )
                        {
                        case MSWCC_EOL:
                            x = 0;
                            if ( ++y == gbm->h )
                                eof4 = TRUE;
                            inx = cLinesWorth * y;
                            break;

                        case MSWCC_EOB:
                            eof4 = TRUE;
                            break;

                        case MSWCC_DELTA:
                            {
                                byte dx = (byte) gbm_read_ahead(ahead);
                                byte dy = (byte) gbm_read_ahead(ahead);

                                x += dx; y += dy;
                                inx = y * cLinesWorth + (x/2);
                
                                if ( y == gbm->h )
                                    eof4 = TRUE;
                            }
                            break;

                        default:
                            {
                                int i, nr = 0;

                                if ( x & 1 )
                                {
                                    for ( i = 0; i+2 <= (int) d; i += 2 )
                                    {
                                        byte b = (byte) gbm_read_ahead(ahead);
                                        data[inx++] |= (b >> 4);
                                        data[inx  ] |= (b << 4);
                                        nr++;
                                    }
                                    if ( i < (int) d )
                                    {
                                        data[inx++] |= ((byte) gbm_read_ahead(ahead) >> 4);
                                        nr++;
                                    }
                                }
                                else
                                {
                                    for ( i = 0; i+2 <= (int) d; i += 2 )
                                    {
                                        data[inx++] = (byte) gbm_read_ahead(ahead);
                                        nr++;
                                    }
                                    if ( i < (int) d )
                                    {
                                        data[inx] = (byte) gbm_read_ahead(ahead);
                                        nr++;
                                    }
                                }
                                x += d;

                                if ( nr & 1 )
                                    gbm_read_ahead(ahead); /* Align input stream to next word */
                            }
                            break;
                        }
                }

                gbm_destroy_ahead(ahead);
            }
            break;

        default:
            return GBM_ERR_BMP_COMP;
        }
    }
    else
    {
        /* OS/2 */
        gbm_file_lseek(fd, (long) bmp_priv->offBits, SEEK_SET);
        gbm_file_read(fd, data, cLinesWorth * gbm->h);
    }

    if ( bmp_priv->invb )
        invert(data, (unsigned) (cLinesWorth * gbm->h));

    return GBM_ERR_OK;
}

static int write_inv(int fd, const byte *buffer, int count)
{
    byte small_buf[1024];
    int so_far = 0, this_go, written;

    while ( so_far < count )
    {
        this_go = min(count - so_far, 1024);
        memcpy(small_buf, buffer + so_far, (size_t) this_go);
        invert(small_buf, (unsigned) this_go);
        if ( (written = gbm_file_write(fd, small_buf, this_go)) != this_go )
            return so_far + written;
        so_far += written;
    }

    return so_far;
}

GBM_ERR bmp_w(const wchar_t *fn, int fd, const GBM *gbm, const GBMRGB *gbmrgb, const byte *data)
{
    const BOOLEAN pm11    = 0;
    const BOOLEAN win     = 0;
    const BOOLEAN inv     = 0;
    const BOOLEAN invb    = 0;

    int cRGB;
    GBMRGB gbmrgb_1bpp[2];

    if ( pm11 && win )
        return GBM_ERR_BAD_OPTION;

    cRGB = ( (1 << gbm->bpp) & 0x1ff );
    /* 1->2, 4->16, 8->256, 24->0 */

    if ( cRGB == 2 )
        /* handle messy 1bpp case */
    {
        /*
          The palette entries inside a 1bpp PM bitmap are not honored, or handled
          correctly by most programs. Current thinking is that they have no actual
          meaning. Under OS/2 PM, bitmap 1's re fg and 0's are bg, and it is the job of
          the displayer to pick fg and bg. We will pick fg=black, bg=white in the bitmap
          file we save. If we do not write black and white, we find that most programs
          will incorrectly honor these entries giving unpredicatable (and often black on
          a black background!) results.
        */

        gbmrgb_1bpp[0].r = gbmrgb_1bpp[0].g = gbmrgb_1bpp[0].b = 0xff;
        gbmrgb_1bpp[1].r = gbmrgb_1bpp[1].g = gbmrgb_1bpp[1].b = 0x00;

        /*
          We observe these values must be the wrong way around to keep most PM
          programs happy, such as WorkPlace Shell WPFolder backgrounds.
        */

        if ( !inv )
            swap_pal(gbmrgb_1bpp);

        gbmrgb = gbmrgb_1bpp;
    }

    if ( pm11 )
    {
        /* OS/2 */
        word usType     = BFT_BMAP;
        word xHotspot   = 0;
        word yHotspot   = 0;
        dword cbFix     = (dword) 12;
        word cx         = (word) gbm->w;
        word cy         = (word) gbm->h;
        word cPlanes    = (word) 1;
        word cBitCount  = (word) gbm->bpp;
        int cLinesWorth = (((cBitCount * cx + 31) / 32) * cPlanes) * 4;
        dword offBits   = (dword) 26 + cRGB * (dword) 3;
        dword cbSize    = offBits + (dword) cy * (dword) cLinesWorth;
        int i, total, actual;

        write_word(fd, usType);
        write_dword(fd, cbSize);
        write_word(fd, xHotspot);
        write_word(fd, yHotspot);
        write_dword(fd, offBits);
        write_dword(fd, cbFix);
        write_word(fd, cx);
        write_word(fd, cy);
        write_word(fd, cPlanes);
        write_word(fd, cBitCount);

        for ( i = 0; i < cRGB; i++ )
        {
            byte b[3];

            b[0] = gbmrgb[i].b;
            b[1] = gbmrgb[i].g;
            b[2] = gbmrgb[i].r;
            if ( gbm_file_write(fd, b, 3) != 3 )
                return GBM_ERR_WRITE;
        }

        total = gbm->h * cLinesWorth;
        if ( invb )
            actual = write_inv(fd, data, total);
        else
            actual = gbm_file_write(fd, data, total);
        if ( actual != total )
            return GBM_ERR_WRITE;
    }
    else
    {
        /* OS/2 and Windows 3.0 */
        word usType         = BFT_BMAP;
        word xHotspot       = 0;
        word yHotspot       = 0;
        dword cbFix         = (dword) 40;
        dword cx            = (dword) gbm->w;
        dword cy            = (dword) gbm->h;
        word cPlanes        = (word) 1;
        word cBitCount      = (word) gbm->bpp;
        int cLinesWorth     = (((cBitCount * (int) cx + 31) / 32) * cPlanes) * 4;
        dword offBits       = (dword) 54 + cRGB * (dword) 4;
        dword cbSize        = offBits + (dword) cy * (dword) cLinesWorth;
        dword ulCompression = BCA_UNCOMP;
        dword cbImage       = (dword) cLinesWorth * (dword) gbm->h;
        dword cxResolution  = 0;
        dword cyResolution  = 0;
        dword cclrUsed      = 0;
        dword cclrImportant = 0;
        int i, total, actual;

        write_word(fd, usType);
        write_dword(fd, cbSize);
        write_word(fd, xHotspot);
        write_word(fd, yHotspot);
        write_dword(fd, offBits);

        write_dword(fd, cbFix);
        write_dword(fd, cx);
        write_dword(fd, cy);
        write_word(fd, cPlanes);
        write_word(fd, cBitCount);
        write_dword(fd, ulCompression);
        write_dword(fd, cbImage);
        write_dword(fd, cxResolution);
        write_dword(fd, cyResolution);
        write_dword(fd, cclrUsed);
        write_dword(fd, cclrImportant);

        for ( i = 0; i < cRGB; i++ )
        {
            byte b[4];

            b[0] = gbmrgb[i].b;
            b[1] = gbmrgb[i].g;
            b[2] = gbmrgb[i].r;
            b[3] = 0;
            if ( gbm_file_write(fd, b, 4) != 4 )
                return GBM_ERR_WRITE;
        }

        total = gbm->h * cLinesWorth;
        if ( invb )
            actual = write_inv(fd, data, total);
        else
            actual = gbm_file_write(fd, data, total);
        if ( actual != total )
            return GBM_ERR_WRITE;
    }

    return GBM_ERR_OK;
}
