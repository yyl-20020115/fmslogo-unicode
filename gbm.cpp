/*

gbm.c - Generalised Bitmap Module

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
   #ifdef WX_PURE
      #include <unistd.h>
   #else
      #include <io.h>
   #endif
   #include <fcntl.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include "gbm.h"
   #include "gbmhelp.h"

   #include "gbmbmp.h"
   #include "gbmgif.h"
   #include "debugheap.h"
#endif


struct FT
{
    GBM_ERR (*query_filetype)(GBMFT *gbmft);
    GBM_ERR (*read_header )(const wchar_t *fn, int fd, GBM *gbm);
    GBM_ERR (*read_palette)(int fd, GBM *gbm, GBMRGB *gbmrgb);
    GBM_ERR (*read_data   )(int fd, GBM *gbm, byte *data);
    GBM_ERR (*write       )(const wchar_t *fn, int fd, const GBM *gbm, const GBMRGB *gbmrgb, const byte *data);
};

static const FT fts[] =
{
    {bmp_qft, bmp_rhdr, bmp_rpal, bmp_rdata, bmp_w},
    {gif_qft, gif_rhdr, gif_rpal, gif_rdata, gif_w}
};

#define	N_FT (sizeof(fts) / sizeof(fts[0]))


static wchar_t *extension(const wchar_t *fn)
{
	wchar_t *dot, *slash;

    if ( (dot = (wchar_t *)wcsrchr(fn, L'.')) == NULL )
        return NULL;

    if ( (slash = (wchar_t *)wcspbrk(fn, L"/\\")) == NULL )
        return dot + 1;

    return ( slash < dot ) ? dot + 1 : NULL;
}


GBMEXPORT int  GBMENTRY gbm_io_open(const wchar_t *fn, int mode)
{ 
    return gbm_file_open(fn, mode); 
}
GBMEXPORT int  GBMENTRY gbm_io_create(const wchar_t *fn, int mode)
{ 
    return gbm_file_create(fn, mode); 
}
GBMEXPORT void GBMENTRY gbm_io_close(int fd)
{ 
    gbm_file_close(fd); 
}
GBMEXPORT long GBMENTRY gbm_io_lseek(int fd, long pos, int whence)
{ 
    return gbm_file_lseek(fd, pos, whence);
}
GBMEXPORT int  GBMENTRY gbm_io_read (int fd, void *buf, int len)
{
    return gbm_file_read(fd, buf, len);
}
GBMEXPORT int  GBMENTRY gbm_io_write(int fd, const void *buf, int len)
{
    return gbm_file_write(fd, buf, len);
}


GBMEXPORT GBM_ERR GBMENTRY gbm_guess_filetype(const wchar_t *fn, int *ft)
{
    if ( fn == NULL || ft == NULL )
        return GBM_ERR_BAD_ARG;

    const wchar_t *ext = 0;
    if ( (ext = extension(fn)) == NULL )
        ext = L"";

    for (int i = 0; i < N_FT; i++ )
    {

		//TODO: FIXME
		GBMFT	gbmft = { 0 };
		wchar_t	buf[100 + 1] = { 0 }, *s = 0;

        fts[i].query_filetype(&gbmft);
        for ( s  = wcstok(wcscpy(buf, gbmft.extensions), L" \t,");
              s != NULL;
              s  = wcstok(NULL, L" \t,") )
            if ( gbm_same(s, ext, (int) wcslen(ext) + 1) )
            {
                *ft = i;
                return GBM_ERR_OK;
            }
    }
    return GBM_ERR_NOT_FOUND;
}


GBMEXPORT GBM_ERR GBMENTRY gbm_query_filetype(int ft, GBMFT *gbmft)
{
    if ( gbmft == NULL )
        return GBM_ERR_BAD_ARG;
    return (*fts[ft].query_filetype)(gbmft);
}


GBMEXPORT GBM_ERR GBMENTRY gbm_read_header(const wchar_t *fn, int fd, int ft, GBM *gbm)
{
    if ( fn == NULL || gbm == NULL )
        return GBM_ERR_BAD_ARG;
    gbm_file_lseek(fd, 0L, SEEK_SET);
    return (*fts[ft].read_header)(fn, fd, gbm);
}


GBMEXPORT GBM_ERR GBMENTRY gbm_read_palette(int fd, int ft, GBM *gbm, GBMRGB *gbmrgb)
{
    if ( gbm == NULL || gbmrgb == NULL )
        return GBM_ERR_BAD_ARG;
    return (*fts[ft].read_palette)(fd, gbm, gbmrgb);
}


GBMEXPORT GBM_ERR GBMENTRY gbm_read_data(int fd, int ft, GBM *gbm, byte *data)
{
    if ( gbm == NULL || data == NULL )
        return GBM_ERR_BAD_ARG;
    return (*fts[ft].read_data)(fd, gbm, data);
}


GBMEXPORT GBM_ERR GBMENTRY gbm_write(const wchar_t *fn, int fd, int ft, const GBM *gbm, const GBMRGB *gbmrgb, const byte *data)
{
    if ( fn == NULL )
        return GBM_ERR_BAD_ARG;
    return (*fts[ft].write)(fn, fd, gbm, gbmrgb, data);
}

