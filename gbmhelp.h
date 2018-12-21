/*

gbmhelp.h - Internal helpers for GBM file I/O stuff

*/

#ifndef GBMHELP_H
#define	GBMHELP_H

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern BOOLEAN      gbm_same(const wchar_t *s1, const wchar_t *s2, size_t n);
extern const wchar_t *gbm_find_word(const wchar_t *str, const wchar_t *substr);
extern const wchar_t *gbm_find_word_prefix(const wchar_t *str, const wchar_t *substr);


extern int  gbm_file_open  (const wchar_t *fn, int mode);
extern int  gbm_file_create(const wchar_t *fn, int mode);
extern void gbm_file_close (int fd);
extern long gbm_file_lseek (int fd, long pos, int whence);
extern int  gbm_file_read  (int fd, void *buf, int len);
extern int  gbm_file_write (int fd, const void *buf, int len);

#define	AHEAD_BUF 0x4000

struct AHEAD
{
    byte buf[AHEAD_BUF];
    int inx, cnt;
    int fd;
};

extern AHEAD *gbm_create_ahead(int fd);
extern void   gbm_destroy_ahead(AHEAD *ahead);
extern int    gbm_read_ahead(AHEAD *ahead);

#endif
