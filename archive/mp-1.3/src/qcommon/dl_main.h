#ifndef DL_MAIN_H
#define DL_MAIN_H

enum dlStatus_t
{
    DL_CONTINUE = 0,
    DL_DONE = 1,
    DL_FAILED = 2
};

int DL_VPrintf(const char *fmt, char *args);
void DL_CancelDownload(void);
void DL_InitDownload(void);
void DL_Shutdown(void);
int DL_BeginDownload(char *localName, const char *remoteUrl);
int DL_BeginDownload(const char *remoteUrl);
int DL_DownloadLoop(void);
bool DL_InProgress(void);
bool DL_DLIsMotd(void);

char *LAN_GetMotdFilename(void);
void CL_ReadMotd(void);
void CL_WWWDownload(void);

#endif
