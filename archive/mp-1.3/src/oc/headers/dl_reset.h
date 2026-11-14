#ifndef DL_RESET_H
#define DL_RESET_H

/* 1.3 download reset: retail expands it at every use, no standalone body */
#define CL_ClearDownloadStateInl() do { \
    cls.downloadRestart = 0; \
    *cls.originalDownloadName = *cls.downloadName = *cls.downloadTempName = 0; \
    cls.wwwDlInProgress = 0; \
    cls.wwwDlDisconnected = 0; \
    cls.downloadFlags = 0; \
    DL_CancelDownload(); \
} while (0)
#endif
