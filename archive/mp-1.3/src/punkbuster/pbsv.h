#ifndef PBSV_H
#define PBSV_H
// PunkBuster server glue (1.2c). Source file and type names from the Mac 1.3 STABS
// (PC/punkbuster/pbsv.cpp, pbsv.h, pbcommon.h).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>

struct stPbSv;

typedef char *(*tdPbGameCommand)(char *, char *);
typedef char *(*tdPbGameQuery)(int, char *);
typedef char *(*tdPbGameMsg)(char *, int);
typedef char *(*tdPbSendToClient)(int, char *, int);
typedef char *(*tdPbAddSvEvent)(stPbSv *, int, int, int, char *, int);
typedef char *(*tdPbProcessPbEvents)(stPbSv *, int);
typedef char *(*tdPbSendToAddrPort)(char *, unsigned short, int, char *);
typedef char *(*tdPbPassConnectString)(stPbSv *, char *, char *);
typedef char *(*tdPbAuthClient)(stPbSv *, char *, int, char *);
typedef void (*tdPbTrapConsole)(stPbSv *, char *, int);

struct stPbSv
{
	unsigned long m_svId;
	void *m_Md5;
	HMODULE m_SvInstance;
	HMODULE m_ClInstance;
	HMODULE m_AgInstance;
	char m_msgPrefix[32];
	char m_cwd[257];
	int m_ReloadServer;
	tdPbGameCommand m_GameCommand;
	tdPbGameQuery m_GameQuery;
	tdPbGameMsg m_GameMsg;
	tdPbSendToClient m_SendToClient;
	tdPbAddSvEvent m_AddPbEvent;
	tdPbProcessPbEvents m_ProcessPbEvents;
	tdPbSendToAddrPort m_SendToAddrPort;
	tdPbPassConnectString m_PassConnectString;
	tdPbAuthClient m_AuthClient;
	tdPbTrapConsole m_TrapConsole;
	void *m_Agent;

	void getBasePath(char *path);
	void copyIfNotExists(char *fn, char *basepath);
	void getHomePath();
	char *makefn(char *buf, char *fn);
	void UnloadClientDll();
	void UnloadAgentDll();
	void uninitialize();
	void initialize();
	void UnloadServerDll();
	char *LoadServerDll();
	char *AddPbEvent(int type, int clientIndex, int datalen, char *data, int retry);
	char *ProcessPbEvents(int n);
	stPbSv();
	~stPbSv();
};

extern stPbSv pbsv;
#endif
