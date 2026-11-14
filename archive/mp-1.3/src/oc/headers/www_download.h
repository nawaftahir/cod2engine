#ifndef WWW_DOWNLOAD_H
#define WWW_DOWNLOAD_H

#include "cod2_feature_config.h"

#if COD2_FEATURE_WWW_DOWNLOAD

#include "../../qcommon/dl_main.h"

#else

typedef enum {
    DL_STATUS_IDLE,
    DL_STATUS_IN_PROGRESS,
    DL_STATUS_DONE,
    DL_STATUS_FAILED,
    DL_STATUS_CANCELLED
} dlStatus_t;

static inline void       DL_InitDownload(void) {}
static inline int        DL_BeginDownload(char *l, const char *u) { (void)l; (void)u; return 0; }
static inline int        DL_BeginDownload(const char *l, const char *u, int c) { (void)l; (void)u; (void)c; return 0; }
static inline int        DL_DownloadLoop(void) { return 0; }
static inline void       DL_CancelDownload(void) {}
static inline int        DL_InProgress(void) { return 0; }
static inline int        DL_DLIsMotd(void) { return 0; }
static inline dlStatus_t DL_GetStatus(void) { return DL_STATUS_IDLE; }

#endif

#endif
