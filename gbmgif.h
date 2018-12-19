/*

gbmgif.h - Graphics Interchange Format support

*/

extern GBM_ERR gif_qft(GBMFT *gbmft);
extern GBM_ERR gif_rhdr(const wchar_t *fn, int fd, GBM *gbm);
extern GBM_ERR gif_rpal(int fd, GBM *gbm, GBMRGB *gbmrgb);
extern GBM_ERR gif_rdata(int fd, GBM *gbm, byte *data);
extern GBM_ERR gif_w(const wchar_t *fn, int fd, const GBM *gbm, const GBMRGB *gbmrgb, const byte *data);
