// gbmsize.cpp - Functions for converting BMP to GIF and GIF to BMP
#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
   #include <stdio.h>
   #include <stdlib.h>
   #include <fcntl.h>
#include <wx/string.h>
   #include "gbm.h"
   #include "debugheap.h"
#endif

#ifdef WX_PURE
   #define O_BINARY 0
#endif

const int FILETYPE_BMP = 0;
const int FILETYPE_GIF = 1;

static
byte * 
gbmReadFile(
    const wchar_t * filename, 
    int          src_filetype,
    int          dst_filetype, 
    GBM        & gbm, 
    GBMRGB     * gbmrgb
    )
{
    GBMFT   gbmft;
    byte    *data;

    int  fd;
    if ( (fd = gbm_io_open(filename, O_RDONLY|O_BINARY)) == -1 )
    {
        // fatal("can't open %s", fn_src);
        return NULL;
    }

    if (gbm_read_header(filename, fd, src_filetype, &gbm) != GBM_ERR_OK)
    {
        gbm_io_close(fd);
        // fatal("can't read header of %s: %s", fn_src, gbm_err(rc));
        return NULL;
    }

    int flag = 0;
    gbm_query_filetype(dst_filetype, &gbmft);
    switch ( gbm.bpp )
    {
    case 24: flag = GBM_FT_W24; break;
    case 8:  flag = GBM_FT_W8;  break;
    case 4:  flag = GBM_FT_W4;  break;
    case 1:  flag = GBM_FT_W1;  break;
    }

    if ( (gbmft.flags & flag) == 0 )
    {
        gbm_io_close(fd);
        // fatal("output bitmap format %s does not support writing %d bpp data", gbmft.short_name, gbm.bpp);
        return NULL;
    }

    if (gbm_read_palette(fd, src_filetype, &gbm, gbmrgb) != GBM_ERR_OK)
    {
        gbm_io_close(fd);
        // fatal("can't read palette of %s: %s", fn_src, gbm_err(rc));
        return NULL;
    }

    int stride = ((gbm.w * gbm.bpp + 31)/32) * 4;
    if ((data = (byte *)malloc(stride * gbm.h)) == NULL)
    {
        gbm_io_close(fd);
        // fatal("out of memory allocating %d bytes for input bitmap", stride * gbm.h);
        return NULL;
    }

    if (gbm_read_data(fd, src_filetype, &gbm, data) != GBM_ERR_OK)
    {
        free(data);
        gbm_io_close(fd);
        //fatal("can't read bitmap data of %s: %s", fn_src, gbm_err(rc));
        return NULL;
    }

    gbm_io_close(fd);

    return data;
}

int gbmBmpToGif(const wchar_t *fn_src, const wchar_t *fn_dst)
{
    GBM     gbm;
    GBMRGB  gbmrgb[0x100];
    byte * data = gbmReadFile(fn_src, FILETYPE_BMP, FILETYPE_GIF, gbm, gbmrgb);
    if (data == NULL)
    {
        return 1;
    }

    int fd;

    extern int bAppendMode;

    if (bAppendMode)
    {
        if ( (fd = gbm_io_open(fn_dst, O_RDWR|O_BINARY)) == -1 )
        {
            free(data);
            // fatal("can't create %s", fn_dst);
            return 7;
        }
        gbm_io_lseek(fd, -1, SEEK_END);
    }
    else
    {
        if ( (fd = gbm_io_create(fn_dst, O_WRONLY|O_BINARY)) == -1 )
        {
            free(data);
            // fatal("can't create %s", fn_dst);
            return 7;
        }
    }

    if (gbm_write(fn_dst, fd, FILETYPE_GIF, &gbm, gbmrgb, data) != GBM_ERR_OK)
    {
        gbm_io_close(fd);
        remove(wxString(fn_dst));
        free(data);
        //fatal("can't write %s: %s", fn_dst, gbm_err(rc));
        return 8;
    }

    gbm_io_close(fd);

    free(data);

    return 0;
}

int gbmGifToBmp(const wchar_t *fn_src, const wchar_t *fn_dst)
{
    GBM       gbm;
    GBMRGB    gbmrgb[0x100];
    byte * data = gbmReadFile(fn_src, FILETYPE_GIF, FILETYPE_BMP, gbm, gbmrgb);
    if (data == NULL)
    {
        return 1;
    }


    int fd;
    if ( (fd = gbm_io_create(fn_dst, O_WRONLY|O_BINARY)) == -1 )
    {
        free(data);
        // fatal("can't create %s", fn_dst);
        return 7;
    }
   
    if (gbm_write(fn_dst, fd, FILETYPE_BMP, &gbm, gbmrgb, data) != GBM_ERR_OK)
    {
        gbm_io_close(fd);
        remove(wxString(fn_dst));
        free(data);
        //fatal("can't write %s: %s", fn_dst, gbm_err(rc));
        return 8;
    }

    gbm_io_close(fd);
    free(data);

    return 0;
}
