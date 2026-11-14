#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#undef chmod

#include "qcommon.h"
#include "com_files.h"
#include "dl_main.h"

#define ERR_FATAL LIBWWW_ERR_FATAL
#include "WWWLib.h"
#include "WWWInit.h"
#include "HTProfil.h"
#include "HTAlert.h"
#include "HTNet.h"
#include "HTEvtLst.h"
#include "HTHost.h"
#include "HTReqMan.h"
#include "HTParse.h"
#include "HTEscape.h"
#include "HTAABrow.h"
#include "HTFTP.h"
#undef ERR_FATAL

static int dl_initialized = 0;
static int dl_running = 0;
static int dl_forceRawBytesCount = 0;
static HTRequest *dl_request = 0;
static int dl_requestStatus = -1000;
bool dl_isMotd;

int DL_VPrintf(const char *fmt, char *args)
{
    char msg[1024];

    _vsnprintf(msg, sizeof(msg), fmt, (va_list)args);
    Com_Printf("%s", msg);
    return strlen(msg);
}

static int terminate_handler(HTRequest *request, HTResponse *response, void *param, int status)
{
    dl_requestStatus = status;
    HTEventList_stopLoop();
    return 0;
}

static int HTAlertCallback_progress(HTRequest *request, HTAlertOpcode opcode, int messageNumber, const char *defaultMessage, void *input, HTAlertPar *reply)
{
    if (opcode != HT_PROG_READ)
        return 1;

    if (!dl_forceRawBytesCount)
    {
        legacyHacks->cl_downloadCount = HTRequest_bytesRead(request);
        return 1;
    }

    if (!HTNet_rawBytesCount(request->net))
    {
        Com_DPrintf("Force raw byte count on request->net %p\n", request->net);
        HTFTP_setRawBytesCount(request);
    }

    legacyHacks->cl_downloadCount = HTFTP_getDNetRawBytesCount(request);
    return 1;
}

static int HTAlertCallback_confirm(HTRequest *request, HTAlertOpcode opcode, int messageNumber, const char *defaultMessage, void *input, HTAlertPar *reply)
{
    if (messageNumber == 9)
    {
        Com_Printf("Replace existing download target file\n");
        return 1;
    }

    Com_Printf("Aborting, unknown libwww confirm message id: %d\n", messageNumber);
    HTEventList_stopLoop();
    return 0;
}

static int HTAlertCallback_prompt(HTRequest *request, HTAlertOpcode opcode, int messageNumber, const char *defaultMessage, void *input, HTAlertPar *reply)
{
    Com_Printf("Aborting, libwww prompt message id: %d (prompted for a login/password?)\n", messageNumber);
    HTEventList_stopLoop();
    return 0;
}

__declspec(noinline) void DL_CancelDownload(void)
{
    if (dl_running)
    {
        HTEventList_unregisterAll();
        HTHost_setEventTimeout(-1);
        dl_running = 0;
    }

    if (dl_request)
    {
        HTRequest_kill(dl_request);
        HTRequest_delete(dl_request);
        dl_request = NULL;
    }
}

void DL_InitDownload(void)
{
    if (!dl_initialized)
    {
        HTProfile_newNoCacheClient("ID_DOWNLOAD", "1.0");
        HTAlertInit();
        HTAlert_setInteractive(1);
        HTPrint_setCallback((HTPrintCallback *)DL_VPrintf);
        HTTrace_setCallback((HTTraceCallback *)DL_VPrintf);
        HTNet_addAfter(terminate_handler, NULL, NULL, 1, (HTFilterOrder)0xffff);
        HTAlert_add(HTAlertCallback_progress, (HTAlertOpcode)0xffff);
        HTAlert_add(HTAlertCallback_confirm, (HTAlertOpcode)0x20000);
        HTAlert_add(HTAlertCallback_prompt, (HTAlertOpcode)0x1c0000);
        Com_Printf("Client download subsystem initialized\n");
        dl_initialized = 1;
    }
}

void DL_Shutdown(void)
{
    if (dl_initialized)
    {
        dl_initialized = 0;
    }
}

int DL_BeginDownload(char *localName, const char *remoteUrl)
{
    char *requestUrl = NULL;
    char *scheme;
    char *host;
    char *path;
    char *hostSeparator;

    if (dl_running)
        DL_CancelDownload();

    dl_requestStatus = -1000;
    if (!localName || !remoteUrl)
    {
        Com_DPrintf("Empty download URL or empty local file name\n");
        return 0;
    }

    DL_InitDownload();
    scheme = HTParse(remoteUrl, "", 16);
    if (!stricmp(scheme, "ftp"))
    {
        dl_forceRawBytesCount = 1;
        HTHost_setEventTimeout(-1);
    }
    else
    {
        dl_forceRawBytesCount = 0;
        HTHost_setEventTimeout(30000);
    }

    dl_request = HTRequest_new();
    if (!stricmp(scheme, "http"))
    {
        host = HTParse(remoteUrl, "", 8);
        path = HTParse(remoteUrl, "", 5);
        hostSeparator = strchr(host, '@');

        if (hostSeparator)
        {
            char *password;
            HTBasic *basic;

            *hostSeparator = '\0';
            password = strchr(host, ':');
            if (password)
            {
                *password++ = '\0';
                HTUnEscape(password);
            }
            HTUnEscape(host);

            basic = HTBasic_new();
            HTSACopy((char **)&basic->uid, host);
            HTSACopy((char **)&basic->pw, password);
            basic_credentials(dl_request, basic);
            HTBasic_delete(basic);

            requestUrl = (char *)HTMemory_malloc(strlen(hostSeparator + 1) + strlen(path) + 8);
            sprintf(requestUrl, "http://%s%s", hostSeparator + 1, path);
            Com_DPrintf("HTTP Basic Auth - %s %s %s\n", host, password, requestUrl);
            HTMemory_free(host);
            HTMemory_free(path);
        }
        else
        {
            HTSACopy(&requestUrl, remoteUrl);
        }
    }
    else
    {
        HTSACopy(&requestUrl, remoteUrl);
    }

    HTMemory_free(scheme);
    FS_CreatePath(localName);
    if (HTLoadToFile(requestUrl, dl_request, localName) != 1)
    {
        Com_DPrintf("HTLoadToFile failed\n");
        HTMemory_free(requestUrl);
        requestUrl = NULL;
        HTProfile_delete();
        return 0;
    }

    HTMemory_free(requestUrl);
    requestUrl = NULL;
    scheme = HTParse(remoteUrl, "", 16);
    host = HTParse(remoteUrl, "", 8);
    path = HTParse(remoteUrl, "", 5);
    hostSeparator = strchr(host, '@');

    if (hostSeparator)
    {
        Com_sprintf(legacyHacks->cl_downloadName, sizeof(legacyHacks->cl_downloadName), "%s://*:*%s%s", scheme, hostSeparator, path);
    }
    else
    {
        Com_sprintf(legacyHacks->cl_downloadName, sizeof(legacyHacks->cl_downloadName), remoteUrl);
    }
    HTMemory_free(path);
    HTMemory_free(host);
    HTMemory_free(scheme);

    if (dl_forceRawBytesCount)
    {
        HTHost_setEventTimeout(30000);
    }

    HTEventList_init(dl_request);
    dl_running = 1;
    return 1;
}

int DL_BeginDownload(const char *remoteUrl)
{
    char *requestUrl = NULL;

    if (dl_running)
        return 0;

    dl_requestStatus = -1000;
    if (!remoteUrl)
    {
        Com_Printf("Empty download URL\n");
        return 0;
    }

    DL_InitDownload();
    dl_forceRawBytesCount = 0;
    HTHost_setEventTimeout(30000);
    dl_request = HTRequest_new();
    HTSACopy(&requestUrl, remoteUrl);

    char *motd = LAN_GetMotdFilename();

    if (!HTLoadToFile(requestUrl, dl_request, motd))
    {
        Com_DPrintf("HTLoadToFile failed\n");
        HTMemory_free(requestUrl);
        requestUrl = NULL;
        HTProfile_delete();
        return 0;
    }

    HTMemory_free(requestUrl);
    requestUrl = NULL;
    HTEventList_init(dl_request);
    dl_running = 1;
    dl_isMotd = 1;
    return 1;
}

int DL_DownloadLoop(void)
{
    if (HTEventList_pump())
        return 0;

    HTEventList_unregisterAll();
    HTHost_setEventTimeout(-1);
    HTRequest_kill(dl_request);
    HTRequest_delete(dl_request);
    dl_request = NULL;
    dl_running = 0;

    if (dl_requestStatus < 0) {
        Com_Printf("DL_DownloadLoop: request terminated with failure status %d\n", dl_requestStatus);
        return 2;
    }

    return 1;
}

bool DL_InProgress(void)
{
    return dl_running > 0;
}

bool DL_DLIsMotd(void)
{
    return dl_isMotd;
}
