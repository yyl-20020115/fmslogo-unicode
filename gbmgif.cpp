/*
gbmgif.cpp - Graphics Interchange Format support
*/

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include "gbm.h"
   #include "gbmhelp.h"
//   #include "debugheap.h"
#endif


#define low_byte(w)     ((byte)  (          (w)&0x00ffU)    )
#define high_byte(w)    ((byte) (((unsigned)(w)&0xff00U)>>8))
#define make_word(a,b)  (((word)a) + (((word)b) << 8))

#define RGB(r,g,b) ((unsigned long)(((byte)(r)|((word)((byte)(g))<<8))|(((dword)(byte)(b))<<16)))

static const GBMFT gif_gbmft =
{
    L"GIF",
    L"CompuServe Graphics Interchange Format",
    L"GIF",
    GBM_FT_R1|GBM_FT_R4|GBM_FT_R8|GBM_FT_W1|GBM_FT_W4|GBM_FT_W8,
};

#define GBM_ERR_GIF_BPP         ((GBM_ERR) 1100)
#define GBM_ERR_GIF_TERM        ((GBM_ERR) 1101)
#define GBM_ERR_GIF_CODE_SIZE   ((GBM_ERR) 1102)
#define GBM_ERR_GIF_CORRUPT     ((GBM_ERR) 1103)
#define GBM_ERR_GIF_HEADER      ((GBM_ERR) 1104)

struct GIF_PRIV
{
    BOOLEAN ilace, errok;
    int     bpp;
    byte    pal[0x100*3];
};

#ifdef _WIN64
typedef unsigned long long cword;
#else
typedef unsigned int cword;
#endif
/* Pass 0 is all lines where  y%8    == 0
   Pass 1 is all lines where (y-4)%8 == 0
   Pass 2 is all lines where (y-2)%4 == 0
   Pass 3 is all lines where (y-1)%2 == 0
   The complexity comes in when you realise there can be < 8 lines in total! */

static int step_ilace(int y, int h, int *pass)
{
    switch ( *pass )
    {
    case 0: y += 8; break;
    case 1: y += 8; break;
    case 2: y += 4; break;
    case 3: y += 2; break;
    }
    if ( y < h ) return y;
    if ( *pass == 0 ) { *pass = 1; y = 4; if ( y < h ) return y; }
    if ( *pass == 1 ) { *pass = 2; y = 2; if ( y < h ) return y; }
    if ( *pass == 2 ) { *pass = 3; y = 1; }
    return y;
}


GBM_ERR gif_qft(GBMFT *gbmft)
{
    *gbmft = gif_gbmft;
    return GBM_ERR_OK;
}


GBM_ERR gif_rhdr(const wchar_t *fn, int fd, GBM *gbm)
{
    GIF_PRIV *gif_priv = (GIF_PRIV *) gbm->priv;
    byte signiture[6], scn_desc[7], image_desc[10];
    int img = -1;
    const int img_want = 0;
    int bits_gct;

    gif_priv->errok = false;

    /* Read and validate signiture block */

    if ( gbm_file_read(fd, signiture, 6) != 6 )
        return GBM_ERR_READ;
    if ( memcmp(signiture, "GIF87a", 6) &&
         memcmp(signiture, "GIF89a", 6) )
        return GBM_ERR_BAD_MAGIC;

    /* Read screen descriptor */

    if ( gbm_file_read(fd, scn_desc, 7) != 7 )
        return GBM_ERR_READ;
    gif_priv->bpp = bits_gct = (scn_desc[4] & 7) + 1;

    if ( scn_desc[4] & 0x80 )
        /* Global colour table follows screen descriptor */
    {
        if ( gbm_file_read(fd, gif_priv->pal, 3 << bits_gct) != (3 << bits_gct) )
            return GBM_ERR_READ;
    }
    else
        /* Blank out palette, but make entry 1 white */
    {
        memset(gif_priv->pal, 0, 3 << bits_gct);
        gif_priv->pal[3] =
            gif_priv->pal[4] =
            gif_priv->pal[5] = 0xff;
    }

    /* Expected image descriptors / extension blocks / terminator */

    while ( img < img_want )
    {
        if ( gbm_file_read(fd, image_desc, 1) != 1 )
            return GBM_ERR_READ;
        switch ( image_desc[0] )
        {
        case 0x2c:
            /* 0x2c image descriptor */
            if ( gbm_file_read(fd, image_desc + 1, 9) != 9 )
                return GBM_ERR_READ;
            gbm->w = make_word(image_desc[5], image_desc[6]);
            gbm->h = make_word(image_desc[7], image_desc[8]);
            gif_priv->ilace = ( (image_desc[9] & 0x40) != 0 );
            
            if ( image_desc[9] & 0x80 )
                /* Local colour table follows */
            {
                gif_priv->bpp = (image_desc[9] & 7) + 1;
                if ( gbm_file_read(fd, gif_priv->pal, 3 << gif_priv->bpp) != (3 << gif_priv->bpp) )
                    return GBM_ERR_READ;
            }

            if ( ++img != img_want )
                /* Skip the image data */
            {
                byte code_size, block_size;
                
                if ( gbm_file_read(fd, &code_size, 1) != 1 )
                    return GBM_ERR_READ;
                do
                {
                    if ( gbm_file_read(fd, &block_size, 1) != 1 )
                        return GBM_ERR_READ;
                    gbm_file_lseek(fd, block_size, SEEK_CUR);
                }
                while ( block_size );
            }

            break;

        case 0x21:
            {
                /* 0x21 extension block */
                /* Ignore all extension blocks */
                byte func_code, byte_count;
            
                if ( gbm_file_read(fd, &func_code, 1) != 1 )
                    return GBM_ERR_READ;
                do
                {
                    if ( gbm_file_read(fd, &byte_count, 1) != 1 )
                        return GBM_ERR_READ;
                    gbm_file_lseek(fd, byte_count, SEEK_CUR);
                }
                while ( byte_count );
            }
            break;

        case 0x3b:
            /* 0x3b terminator */
            /* Oi, we were hoping to get an image descriptor! */
            return GBM_ERR_GIF_TERM;

        default:
            return GBM_ERR_GIF_HEADER;
        }
    }
   
    switch ( gif_priv->bpp )
    {
    case 1:  gbm->bpp = 1; break;
    case 2:
    case 3:
    case 4:  gbm->bpp = 4; break;
    case 5:
    case 6:
    case 7:
    case 8:  gbm->bpp = 8; break;
    default: return GBM_ERR_GIF_BPP;
    }

    return GBM_ERR_OK;
}


GBM_ERR gif_rpal(int fd, GBM *gbm, GBMRGB *gbmrgb)
{
    GIF_PRIV *gif_priv = (GIF_PRIV *) gbm->priv;
    byte *pal = gif_priv->pal;
    int i;

    memset(gbmrgb, 0x80, (sizeof(GBMRGB) << gbm->bpp));

    for ( i = 0; i < (1 << gif_priv->bpp); i++ )
    {
        gbmrgb[i].r = *pal++;
        gbmrgb[i].g = *pal++;
        gbmrgb[i].b = *pal++;
    }

    return GBM_ERR_OK;
}

struct READ_CONTEXT
{
    int fd;           /* File descriptor to read */
    int inx, size;    /* Index and size in bits */
    byte buf[255+3];  /* Buffer holding bits */
    int code_size;    /* Number of bits to return at once */
    cword read_mask;  /* 2^code_size-1 */
};

static cword read_code(READ_CONTEXT *c)
{
    dword raw_code; int byte_inx;

    while ( c->inx + c->code_size > c->size )
        /* not enough bits in buffer refill it */
        /* Not very efficient, but infrequently called */
    {
        int bytes_to_lose = ((unsigned) c->inx >> 3);
        byte bytes;

        /* Note biggest code size is 12 bits */
        /* And this can at worst span 3 bytes */
        memcpy(c->buf, c->buf + bytes_to_lose, 3);
        (c->inx) &= 7;
        (c->size) -= (bytes_to_lose << 3);
        if ( gbm_file_read(c->fd, &bytes, 1) != 1 )
            return 0xffff;
        if ( gbm_file_read(c->fd, c->buf + ((unsigned) c->size >> 3), bytes) != bytes )
            return 0xffff;
        (c->size) += (bytes << 3);
    }

    byte_inx = ((unsigned) c->inx >> 3);
    raw_code = c->buf[byte_inx] + ((c->buf[byte_inx + 1]) << 8);
    if ( c->code_size > 8 )
        raw_code += ((c->buf[byte_inx + 2]) << 16);
    raw_code >>= ((c->inx) & 7U);
    (c->inx) += (byte) (c->code_size);
   
    return (cword) raw_code & c->read_mask;
}


struct OUTPUT_CONTEXT
{
    int x, y, w, h, bpp, pass;
    BOOLEAN ilace;
    int stride;
    byte *data, *data_this_line;
};

static void output(byte value, OUTPUT_CONTEXT *o)
{
    if ( o->y >= o->h )
        return;

    switch ( o->bpp )
    {
    case 1:
        if ( (o->x) & 7U )
            o->data_this_line[(unsigned)(o->x) >> 3] |= (value << (7 - (((unsigned)o->x) & 7U)));
        else
            o->data_this_line[(unsigned)(o->x) >> 3] = (value << 7);
        break;
    case 4:
        if ( (o->x) & 1U )
            o->data_this_line[(unsigned)(o->x) >> 1] |= value;
        else
            o->data_this_line[(unsigned)(o->x) >> 1] = (value << 4);
        break;
    case 8:
        o->data_this_line[o->x] = value;
        break;
    }
   
    if ( ++(o->x) < o->w )
        return;

    o->x = 0;
    if ( o->ilace )
    {
        o->y = step_ilace(o->y, o->h, &(o->pass));
        o->data_this_line = o->data + (o->h - 1 - o->y) * o->stride;
    }
    else
    {
        (o->y)++;
        o->data_this_line -= (o->stride);
    }
}

GBM_ERR gif_rdata(int fd, GBM *gbm, byte *data)
{
    GIF_PRIV *gif_priv = (GIF_PRIV *) gbm->priv;
    byte min_code_size;          /* As read from the file */
    int init_code_size;          /* Initial code size */
    cword max_code;                      /* 1 << code_size */
    cword clear_code;            /* Code to clear table */
    cword eoi_code;                      /* End of information code */
    cword first_free_code;               /* First free code */
    cword free_code;             /* Next available free code slot */
    word bit_mask;                       /* Output pixel mask */ 
    int i, out_count = 0;
    cword code = 0, cur_code = 0, old_code = 0, in_code = 0, fin_char = 0;
    cword *prefix, *suffix, *outcode;
    READ_CONTEXT c;
    OUTPUT_CONTEXT o;
    BOOLEAN table_full = FALSE;  /* To help implement deferred clear */

    if ( (prefix = (cword *) malloc((size_t) (4096 * sizeof(cword)))) == NULL )
        return GBM_ERR_MEM;
    if ( (suffix = (cword *) malloc((size_t) (4096 * sizeof(cword)))) == NULL )
    {
        free(prefix);
        return GBM_ERR_MEM;
    }
    if ( (outcode = (cword *) malloc((size_t) (4097 * sizeof(cword)))) == NULL )
    {
        free(suffix);             
        free(prefix);
        return GBM_ERR_MEM;
    }

    if ( gbm_file_read(fd, &min_code_size, 1) != 1 )
    { 
        free(outcode);
        free(suffix);
        free(prefix);
        return GBM_ERR_READ;
    }

    if ( min_code_size < 2 || min_code_size > 9 )
    { 
        free(outcode);
        free(suffix);
        free(prefix);
        return GBM_ERR_GIF_CODE_SIZE;
    }

    /* Initial read context */

    c.inx            = 0;
    c.size           = 0;
    c.fd             = fd;
    c.code_size      = min_code_size + 1;
    c.read_mask      = (cword) (( 1 << c.code_size ) - 1);

    /* Initialise pixel-output context */
   
    o.x              = 0;
    o.y              = 0;
    o.pass           = 0;
    o.w              = gbm->w;
    o.h              = gbm->h;
    o.bpp            = gbm->bpp;
    o.ilace          = gif_priv->ilace;
    o.stride         = ( (gbm->w * gbm->bpp + 31) / 32 ) * 4;
    o.data           = data;
    o.data_this_line = data + (gbm->h - 1) * o.stride;

    bit_mask = (word) ((1 << gif_priv->bpp) - 1);

    /* 2^min_code size accounts for all colours in file */

	clear_code = (cword)(
#ifdef _WIN64
		1LL
#else
		1
#endif
		<< min_code_size);
    eoi_code = (cword) (clear_code + 1);
    free_code = first_free_code = (cword) (clear_code + 2);

    /* 2^(min_code_size+1) includes clear and eoi code and space too */

    init_code_size = c.code_size;
    max_code = (cword) ( 
#ifdef _WIN64
		1LL
#else
		1
#endif		
		<< c.code_size );

    while ( (code = read_code(&c)) != eoi_code && code != 0xffff && o.y < o.h )
    {
        if ( code == clear_code )
        {
            c.code_size = init_code_size;
            max_code = (cword) ( 
#ifdef _WIN64
				1LL
#else
				1
#endif
				<< c.code_size );
            c.read_mask = (cword) (max_code - 1);
            free_code = first_free_code;
            cur_code = old_code = code = read_code(&c);
            if ( code == 0xffff )
                break;
            fin_char = (cur_code & bit_mask);
            output((byte) fin_char, &o);
            table_full = FALSE;
        }
        else
        {
            cur_code = in_code = code;
            if ( cur_code >= free_code )
            {
                cur_code = old_code;
                outcode[out_count++] = fin_char;
            }
            while ( cur_code > bit_mask )
            {
                if ( out_count > 4096 )
                {
                    free(outcode);
                    free(suffix);
                    free(prefix);
                    return gif_priv->errok ? GBM_ERR_OK : GBM_ERR_GIF_CORRUPT;
                }
                outcode[out_count++] = suffix[cur_code];
                cur_code = prefix[cur_code];
            }
            fin_char = (cur_code & bit_mask);
            outcode[out_count++] = fin_char;
            for ( i = out_count - 1; i >= 0; i-- )
                output((byte) outcode[i], &o);
            out_count = 0;
         
            /* Update dictionary */

            if ( !table_full )
            {
                prefix[free_code] = old_code;
                suffix[free_code] = fin_char;
            
                /* Advance to next free slot */
            
                if ( ++free_code >= max_code )
                {
                    if ( c.code_size < 12 )
                    {
                        c.code_size++;
                        max_code <<= 1;
                        c.read_mask = (cword) (( 1 << c.code_size ) - 1);
                    }
                    else
                        table_full = TRUE;
                }
            }
            old_code = in_code;
        }
    }
   
    free(outcode);
    free(suffix);
    free(prefix);

    if ( code == 0xffff )
        return gif_priv->errok ? GBM_ERR_OK : GBM_ERR_READ;
   
    return GBM_ERR_OK;
}

/*
  We won't write any GIF89a or higher extensions into file.
  Write palette as global colour table, not local.
*/

struct WRITE_CONTEXT
{
    int fd;          /* Open file descriptor to write to */
    int inx;         /* Bit index into buf */
    int code_size;   /* Code size in bits */
    byte buf[255+2]; /* Biggest block + overflow space */
};

static BOOLEAN write_code(cword code, WRITE_CONTEXT *w)
{
    byte *buf = w->buf + ((unsigned)w->inx >> 3);

    code <<= ((w->inx) & 7);
    *buf++ |= (byte)  code       ;
    *buf++  = (byte) (code >>  8);
    *buf    = (byte) (code >> 16);

    (w->inx) += (w->code_size);
    if ( w->inx >= 255 * 8 )
        /* Flush out full buffer */
    {
        byte bytes = 255;

        if ( gbm_file_write(w->fd, &bytes, 1) != 1 )
            return FALSE;
        if ( gbm_file_write(w->fd, w->buf, 255) != 255 )
            return FALSE;

        memcpy(w->buf, w->buf + 255, 2);
        memset(w->buf + 2, 0, 255);
        (w->inx) -= (255 * 8);
    }

    return TRUE;
}

static BOOLEAN flush_code(WRITE_CONTEXT *w)
{
    byte bytes = ((unsigned)(w->inx + 7) >> 3);
   
    if ( bytes )
    {
        if ( gbm_file_write(w->fd, &bytes, 1) != 1 )
            return FALSE;
        if ( gbm_file_write(w->fd, w->buf, bytes) != bytes )
            return FALSE;
    }

    /* Data block terminator - a block of zero size */

    bytes = 0;
    return gbm_file_write(w->fd, &bytes, 1) == 1;
}


struct DICT { cword tail; byte col; };

GBMRGB global_gbmrgb[0x100];

GBM_ERR gif_w(const wchar_t *fn, int fd, const GBM *gbm, const GBMRGB *gbmrgb, const byte *data)
{
    const int xpos           = 0;
    const int ypos           = 0;
    const int xscreen        = gbm->w;
    const int yscreen        = gbm->h;
    const int inx_background = 0;
    const int inx_transcol   = -1;
    const int ilace          = 0;

    if ( gbm->bpp != 1 && gbm->bpp != 4 && gbm->bpp != 8 )
        return GBM_ERR_NOT_SUPP;

    {
        extern int iDelay;
        extern int bAppendMode;
        extern int iLoop;
        extern int iTrans;
 
        byte scn_desc[7], image_desc[10]; int p;
        int iLocal;

        if (!bAppendMode)
        {

            const char *sig = ((inx_transcol != -1) || (iTrans != -1) || (iDelay != -1)) ? "GIF89a" : "GIF87a";

            /* Write signiture */

            if ( gbm_file_write(fd, sig, 6) != 6 )
                return GBM_ERR_WRITE;

            /* Write screen descriptor */

            scn_desc[0] = low_byte(xscreen);
            scn_desc[1] = high_byte(xscreen);
            scn_desc[2] = low_byte(yscreen);
            scn_desc[3] = high_byte(yscreen);
            scn_desc[4] = (0x80 | ((gbm->bpp - 1) * 0x11));
            /* Global colour table follows */
            /* Quality bpp == gct bpp == gbm->bpp */
            scn_desc[5] = (byte) inx_background;
            scn_desc[6] = 0;
            if ( gbm_file_write(fd, scn_desc, 7) != 7 )
                return GBM_ERR_WRITE;

            /* Write global colour table */

            for ( p = 0; p < (1 << gbm->bpp); p++ )
            {
                byte pal[3];

                pal[0] = gbmrgb[p].r;
                pal[1] = gbmrgb[p].g;
                pal[2] = gbmrgb[p].b;
                global_gbmrgb[p] = gbmrgb[p];
                if ( gbm_file_write(fd, pal, 3) != 3 )
                    return GBM_ERR_WRITE;
            }

            if (iLoop != -1)
            {
                /* Do GIF89a "Graphic Application Extension" application extension block */
                char gae[19];
                gae[0]  = 0x21;             /* Extension Introducer */
				gae[1] = -1;// 0xFF;             /* Graphic Control Label */
                gae[2]  = 0x0B;             /* Block size */
                gae[3]  = 'N';              /* Identifier */
                gae[4]  = 'E';
                gae[5]  = 'T';
                gae[6]  = 'S';
                gae[7]  = 'C';
                gae[8]  = 'A';
                gae[9]  = 'P';
                gae[10] = 'E';
                gae[11] = '2';              /* AuthentCode */
                gae[12] = '.';
                gae[13] = '0';
                gae[14] = 3;                /* SubBlock Length 3 */
                gae[15] = 0x01;             /* Enable Looping */
                gae[16] = low_byte(iLoop);  /* Loop count 0 = inf */
                gae[17] = high_byte(iLoop);
                gae[18] = 0x00;             /* Block size, 0 => end of extension */
                if ( gbm_file_write(fd, gae, 19) != 19 )
                    return GBM_ERR_WRITE;
            }
      
        }

        if ((iDelay != -1) || (iTrans != -1))
        {
            /* Do GIF89a "Graphic Control Extension" application extension block */
            char gce[8];
            gce[0] = 0x21;        /* Extension Introducer */
            gce[1] = (char) 0xF9; /* Graphic Control Label */
            gce[2] = 4;           /* Block size */
            gce[3] = 0x00;        /* No transparent and no overwrite */
            gce[4] = 0;           /* Delay time, 0 => not set */
            gce[5] = 0;           /* Delay time, 0 => not set */
            gce[6] = 0x00;        /* Transparent colour index */
            gce[7] = 0x00;        /* Block size, 0 => end of extension */

            if (iDelay != -1)
            {
                gce[4] = low_byte(iDelay);  /* Delay time (low) */
                gce[5] = high_byte(iDelay); /* Delay time (high) */
            }

            if (iTrans != -1)
            {
                gce[3] |= 0x11;    /* Set Transparent and Overwrite Bits */
                for ( p = 0; p < (1 << gbm->bpp); p++ )
                {
                    if (RGB(gbmrgb[p].r, gbmrgb[p].g, gbmrgb[p].b) == (unsigned)iTrans)
                    {
                        gce[6] = p;
                        break;
                    }
                }
            }

            if ( gbm_file_write(fd, gce, 8) != 8 )
                return GBM_ERR_WRITE;
        }

        if ( inx_transcol != -1 )
            /* Do GIF89a "Graphic Control Extension" application extension block */
        {
            char gce[8];
            gce[0] = 0x21;                    /* Extension Introducer */
            gce[1] = (char) 0xf9;             /* Graphic Control Label */
            gce[2] = 4;                       /* Block size */
            gce[3] = 0x01;                    /* No 'disposal', no 'user input' */
            /* Just transparent index present */
            gce[4] = 0;                       /* Delay time, 0 => not set */
            gce[5] = 0;                       /* Delay time, 0 => not set */
            gce[6] = (char) inx_transcol;     /* Transparent colour index */
            gce[7] = 0;                       /* Block size, 0 => end of extension */
            if ( gbm_file_write(fd, gce, 8) != 8 )
                return GBM_ERR_WRITE;
        }

        /* Do image descriptor block */

        image_desc[0] = (byte) 0x2c;
        image_desc[1] = low_byte(xpos);
        image_desc[2] = high_byte(xpos);
        image_desc[3] = low_byte(ypos);
        image_desc[4] = high_byte(ypos);
        image_desc[5] = low_byte(gbm->w);
        image_desc[6] = high_byte(gbm->w);
        image_desc[7] = low_byte(gbm->h);
        image_desc[8] = high_byte(gbm->h);
        image_desc[9] = (0x30 | (gbm->bpp - 1));

        // check if we need a local color table

        iLocal = 0;

        for ( p = 0; p < (1 << gbm->bpp); p++ )
        {
            if (global_gbmrgb[p].r != gbmrgb[p].r) iLocal = 1;
            if (global_gbmrgb[p].g != gbmrgb[p].g) iLocal = 1;
            if (global_gbmrgb[p].b != gbmrgb[p].b) iLocal = 1;
        }

        if ( iLocal )
            image_desc[9] |= 0x80;

        /* Non-interlaced, no local colour map, no sorted palette */

        if ( ilace )
            image_desc[9] |= 0x40; /* Interlaced */
        if ( gbm_file_write(fd, image_desc, 10) != 10 )
            return GBM_ERR_WRITE;

        /* Write local colour table */

        if ( iLocal )
        {
            for ( p = 0; p < (1 << gbm->bpp); p++ )
            {
                byte pal[3];
         
                pal[0] = gbmrgb[p].r;
                pal[1] = gbmrgb[p].g;
                pal[2] = gbmrgb[p].b;
                if ( gbm_file_write(fd, pal, 3) != 3 )
                    return GBM_ERR_WRITE;
            }
        }
    }

    /*LZW encode data tail col lookup */
    /*
      hashvalue is calculated from a string of pixels cumulatively.
      hashtable is searched starting at index hashvalue for to find the entry.
      hashtable is big enough so that MAX_HASH > 4*MAX_DICT.
    */

#define MAX_HASH        17777                   /* Probably prime and > 4096 */
#define MAX_DICT        4096                    /* Dictionary size           */
#define INIT_HASH(p)    (((p)+3)*301)           /* Initial hash value        */

    {
        int stride = ((gbm->w * gbm->bpp + 31) / 32) * 4;
        byte min_code_size = 0;
        int init_code_size = 0, x = 0, y = 0, pass = 0;
        cword clear_code = 0, eoi_code = 0, last_code = 0, max_code = 0, tail = 0;
        unsigned int hashvalue = 0, lenstring = 0, j = 0;
        DICT *dict, **hashtable = 0;
        WRITE_CONTEXT w;
   
        /* Now LZW encode data */

        if ( (dict = (DICT *) malloc((size_t) (MAX_DICT * sizeof(DICT)))) == NULL )
            return GBM_ERR_MEM;
   
        if ( (hashtable = (DICT **) malloc((size_t) (MAX_HASH * sizeof(DICT *)))) == NULL )
        {
            free(dict);
            return GBM_ERR_MEM;
        }

        /* Initialise encoder variables */

        init_code_size = gbm->bpp + 1;
        if ( init_code_size == 2 )
            /* Room for col0, col1, cc, eoi, but no others! */
            init_code_size++;

        min_code_size = init_code_size - 1;
        if ( gbm_file_write(fd, &min_code_size, 1) != 1 )
        {
            free(hashtable);
            free(dict);
            return GBM_ERR_WRITE;
        }

        clear_code = ( 
#ifdef _WIN64
			1LL
#else
			1
#endif
			<< min_code_size );
        eoi_code   = clear_code + 1;
        last_code  = eoi_code;
        max_code   = ( 
#ifdef _WIN64
			1LL
#else
			1
#endif
			<< init_code_size );
        lenstring  = 0;

        /* Setup write context */

        w.fd        = fd;
        w.inx       = 0;
        w.code_size = init_code_size;
        memset(w.buf, 0, sizeof(w.buf));

        if ( !write_code(clear_code, &w) )
        {
            free(hashtable);
            free(dict);
            return GBM_ERR_WRITE;
        }

        for ( j = 0; j < MAX_HASH; j++ )
            hashtable[j] = NULL;

        data += ( (gbm->h - 1) * stride );
        for ( y = pass = 0; y < gbm->h; )
        {
            const byte *pdata = data - y * stride;
            for ( x = 0; x < gbm->w; x++ )
            {
                byte col;
                /*...sget col:24:*/
                switch ( gbm->bpp )
                {
                case 8:
                    col = *pdata++;
                    break;
                case 4:
                    if ( x & 1 )
                        col = (*pdata++ & 0x0f);
                    else
                        col = (*pdata >> 4);
                    break;
                default: /* must be 1 */
                    if ( (x & 7) == 7 )
                        col = (*pdata++ & 0x01);
                    else
                        col = ((*pdata >> (7-(x&7))) & 0x01);
                    break;
                }

                if ( ++lenstring == 1 )
                {
                    tail      = col;
                    hashvalue = INIT_HASH(col);
                }
                else
                {
                    hashvalue *= ( col + lenstring + 4 );
                    j = ( hashvalue %= MAX_HASH );
                    while ( hashtable[j] != NULL &&
                            ( hashtable[j]->tail != tail ||
                              hashtable[j]->col  != col  ) )
                        if ( ++j >= MAX_HASH )
                            j = 0;
                    if ( hashtable[j] != NULL )
                        /* Found in the strings table */
                        tail = (hashtable[j]-dict);
                    else
                        /* Not found */
                    {
                        if ( !write_code(tail, &w) )
                        {
                            free(hashtable);
                            free(dict);
                            return GBM_ERR_WRITE;
                        }
                        hashtable[j]       = dict + ++last_code;
                        hashtable[j]->tail = tail;
                        hashtable[j]->col  = col;
                        tail               = col;
                        hashvalue          = INIT_HASH(col);
                        lenstring          = 1;
               
                        if ( last_code >= max_code )
                            /* Next code will be written longer */
                        {
                            max_code <<= 1;
                            w.code_size++;
                        }
                        else if ( last_code >= MAX_DICT-2 )
                            /* Reset tables */
                        {
                            if ( !write_code(tail      , &w) ||
                                 !write_code(clear_code, &w) )
                            {
                                free(hashtable);
                                free(dict);
                                return GBM_ERR_WRITE;
                            }
                            lenstring   = 0;
                            last_code   = eoi_code;
                            w.code_size = init_code_size;
                            max_code    = ( 								
#ifdef _WIN64
								1LL
#else
								1
#endif
								<< init_code_size );
                            for ( j = 0; j < MAX_HASH; j++ )
                                hashtable[j] = NULL;
                        }
                    }
                }
         
            }
            if ( ilace )
                y = step_ilace(y, gbm->h, &pass);
            else
                y++;
        }
   
        free(hashtable);
        free(dict);
   
        if ( !write_code(tail    , &w) ||
             !write_code(eoi_code, &w) ||
             !flush_code(          &w) )
            return GBM_ERR_WRITE;
    }

    {
        byte term = (byte) 0x3b;
        if ( gbm_file_write(fd, &term, 1) != 1 )
            return GBM_ERR_WRITE;
    }

    return GBM_ERR_OK;
}
