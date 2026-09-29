/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// unix_main.c

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dlfcn.h>
#include <fpu_control.h>
#include <termios.h>

#include "../qcommon/qcommon.h"
#include "../qcommon/cmd.h"
#include "../qcommon/netchan.h"
#include "../universal/universal_public.h"
#include "linux_local.h"


// dedicated server 1.0 build stamp
#define BUILD_DATE "Oct 25 2005"
#define BUILD_TIME "18:23:51"

unsigned sys_frame_time;
uid_t saved_euid;
qboolean stdin_active = qtrue;

// enable/disabled tty input mode
static dvar_t *ttycon = NULL;
// general flag to tell about tty console mode
static qboolean ttycon_on = qfalse;
// when printing general stuff to stdout stderr (Sys_Printf)
//   we need to disable the tty console stuff
// this increments so we can recursively disable
static int ttycon_hide = 0;
// some key codes that the terminal may be using
static int tty_erase;
static int tty_eof;

static struct termios tty_tc;

static field_t tty_con;

// history
#define TTY_HISTORY 32
static field_t ttyEditLines[TTY_HISTORY];
static int hist_current = -1, hist_count = 0;

void Sys_DoStartProcess( char *cmdline );

// re-exec command staged by Sys_StartProcess; empty means "just quit"
char exit_cmdline[1024] = "";

static const dvar_t *arch;
static const dvar_t *usernameDvar;

void tty_Show();
void Com_SyncThreads();

qboolean Sys_LowPhysicalMemory()
{
	return qfalse;
}

int Sys_FunctionCmp( void *f1, void *f2 )
{
	return qtrue;
}

int Sys_FunctionCheckSum( void *f1 )
{
	return 0;
}

void Sys_BeginProfiling()
{
}

void Sys_In_Restart_f( void )
{
}

// flush stdin, some terminals send a lot of junk
void tty_FlushIn()
{
	char key;

	while ( read(0, &key, 1) != -1 )
		;
}

// do a backspace; some terminals need the full "\b \b"
void tty_Back()
{
	char key;

	key = '\b';
	write(1, &key, 1);
	key = ' ';
	write(1, &key, 1);
	key = '\b';
	write(1, &key, 1);
}

// clear the display of the line currently edited
// bring cursor back to beginning of line
void tty_Hide()
{
	int i;

	if ( ttycon_hide )
	{
		ttycon_hide++;
		return;
	}
	if ( tty_con.cursor > 0 )
	{
		for ( i = 0; i < tty_con.cursor; i++ )
		{
			tty_Back();
		}
	}
	ttycon_hide++;
}

// show the current line
void tty_Show()
{
	int i;

	ttycon_hide--;
	if ( ttycon_hide == 0 )
	{
		if ( tty_con.cursor )
		{
			for ( i = 0; i < tty_con.cursor; i++ )
			{
				write(1, tty_con.buffer + i, 1);
			}
		}
	}
}

// never exit without calling this, or your terminal will be left in a pretty bad state
void Sys_ConsoleInputShutdown()
{
	if ( ttycon_on )
	{
		Com_Printf("Shutdown tty console\n");
		tcsetattr(0, TCSADRAIN, &tty_tc);
	}
}

void Hist_Add( field_t *field )
{
	int i;

	// make some room
	for ( i = TTY_HISTORY - 1; i > 0; i-- )
	{
		ttyEditLines[i] = ttyEditLines[i - 1];
	}
	ttyEditLines[0] = *field;
	if ( hist_count < TTY_HISTORY )
	{
		hist_count++;
	}
	hist_current = -1;
}

field_t *Hist_Prev()
{
	int hist_prev;

	hist_prev = hist_current + 1;
	if ( hist_prev >= hist_count )
	{
		return NULL;
	}
	hist_current++;
	return &ttyEditLines[hist_current];
}

field_t *Hist_Next()
{
	if ( hist_current >= 0 )
	{
		hist_current--;
	}
	if ( hist_current == -1 )
	{
		return NULL;
	}
	return &ttyEditLines[hist_current];
}

// single exit point (regular exit or in case of signal fault)
void Sys_Exit( int ex )
{
	Sys_ConsoleInputShutdown();

	if ( exit_cmdline[0] )
	{
		// give the console and the network stack a moment before handing over
		sleep(1);
		Sys_DoStartProcess(exit_cmdline);
		sleep(1);
	}

	exit(ex);
}

void Sys_Quit( void )
{
	Dvar_Shutdown();
	Cmd_Shutdown();
	Hunk_Shutdown();
	fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) & ~FNDELAY);
	Sys_Exit(0);
}

void Sys_Init( void )
{
	unsigned short dvarFlags;

	Cmd_AddCommand("in_restart", Sys_In_Restart_f);
	arch = Dvar_RegisterString("arch", "linux i386", (dvarFlags = DVAR_ROM | DVAR_CHANGEABLE_RESET));
	usernameDvar = Dvar_RegisterString("username", Sys_GetCurrentUser(), DVAR_ROM | DVAR_CHANGEABLE_RESET);
}

void Sys_Error( const char *error, ... )
{
	va_list argptr;
	char string[1024];

	// change stdin to non blocking
	fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) & ~FNDELAY);

	// don't bother do a show on this one heh
	if ( ttycon_on )
	{
		tty_Hide();
	}

	va_start(argptr, error);
	vsprintf(string, error, argptr);
	va_end(argptr);
	fprintf(stderr, "Sys_Error: %s\n", string);

	Sys_Exit(1);
}

void Sys_Warn( char *warning, ... )
{
	va_list argptr;
	char string[1024];

	va_start(argptr, warning);
	vsprintf(string, warning, argptr);
	va_end(argptr);

	if ( ttycon_on )
	{
		tty_Hide();
	}

	fprintf(stderr, "Warning: %s", string);

	if ( ttycon_on )
	{
		tty_Show();
	}
}

// returns -1 if not present
int Sys_FileTime( char *path )
{
	struct stat buf;

	if ( stat(path, &buf) == -1 )
	{
		return -1;
	}

	return buf.st_mtime;
}

void floating_point_exception_handler( int whatever )
{
	signal(SIGFPE, floating_point_exception_handler);
}

// initialize the console input (tty mode if wanted and possible)
void Sys_ConsoleInputInit()
{
	struct termios tc;

	memset(&tc, 0, sizeof(tc));

	// if the process is backgrounded (running non interactively)
	// then SIGTTIN or SIGTOU is emitted, if not caught, turns into a SIGSTP
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

	ttycon = Dvar_RegisterBool("ttycon", 1, DVAR_CHANGEABLE_RESET | DVAR_INIT);
	Dvar_SetBool(ttycon, 0);
	if ( Dvar_GetBool("ttycon") )
	{
		if ( isatty(STDIN_FILENO) != 1 )
		{
			Com_Printf("stdin is not a tty, tty console mode failed\n");
			Dvar_SetBool(ttycon, 0);
			ttycon_on = qfalse;
			return;
		}
		Com_Printf("Started tty console (use +set ttycon 0 to disable)\n");
		Field_Clear(&tty_con);
		tcgetattr(0, &tty_tc);
		tty_erase = tc.c_cc[VERASE];
		tty_eof = tc.c_cc[VEOF];
		tc = tty_tc;
		// ECHO: don't echo input characters
		// ICANON: enable canonical mode
		tc.c_lflag &= ~(ECHO | ICANON);
		// ISTRIP strip off bit 8, INPCK enable input parity checking
		tc.c_iflag &= ~(ISTRIP | INPCK);
		tc.c_cc[VMIN] = 1;
		tc.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &tc);
		ttycon_on = qtrue;
	}
	else
	{
		ttycon_on = qfalse;
	}
}

char *Sys_ConsoleInput( void )
{
	// we use this when sending back commands
	static char text[256];
	int i;
	int avail;
	char key = 0;
	field_t *history;

	if ( Dvar_GetBool("ttycon") )
	{
		avail = read(0, &key, 1);
		if ( avail != -1 )
		{
			// backspace?
			if ( key == tty_erase || key == 127 || key == 8 )
			{
				if ( tty_con.cursor > 0 )
				{
					tty_con.cursor--;
					tty_con.buffer[tty_con.cursor] = '\0';
					tty_Back();
				}
				return NULL;
			}
			// check if this is a control char
			if ( key && key < ' ' )
			{
				if ( key == '\n' )
				{
					// push it in history
					Hist_Add(&tty_con);
					strcpy(text, tty_con.buffer);
					Field_Clear(&tty_con);
					key = '\n';
					write(1, &key, 1);
					return text;
				}
				if ( key == '\t' )
				{
					tty_Hide();
					Field_CompleteCommand(&tty_con);
					// completion adds a '\' at the beginning of the string
					// and the cursor doesn't reflect the actual length
					tty_con.cursor = strlen(tty_con.buffer);
					if ( tty_con.cursor > 0 )
					{
						if ( tty_con.buffer[0] == '\\' )
						{
							for ( i = 0; i <= tty_con.cursor; i++ )
							{
								tty_con.buffer[i] = tty_con.buffer[i + 1];
							}
							tty_con.cursor--;
						}
					}
					tty_Show();
					return NULL;
				}
				avail = read(0, &key, 1);
				if ( avail != -1 )
				{
					// VT 100 keys
					if ( key == '[' || key == 'O' )
					{
						avail = read(0, &key, 1);
						if ( avail != -1 )
						{
							switch ( key )
							{
							case 'A':
								history = Hist_Prev();
								if ( history )
								{
									tty_Hide();
									tty_con = *history;
									tty_Show();
								}
								tty_FlushIn();
								return NULL;
								break;
							case 'B':
								history = Hist_Next();
								tty_Hide();
								if ( history )
								{
									tty_con = *history;
								}
								else
								{
									Field_Clear(&tty_con);
								}
								tty_Show();
								tty_FlushIn();
								return NULL;
								break;
							case 'C':
								return NULL;
							case 'D':
								return NULL;
							}
						}
					}
				}
				Com_DPrintf("droping ISCTL sequence: %d, tty_erase: %d\n", key, tty_erase);
				tty_FlushIn();
				return NULL;
			}
			// push regular character
			tty_con.buffer[tty_con.cursor] = key;
			tty_con.cursor++;
			// print the current line (this is differential)
			write(1, &key, 1);
		}
		return NULL;
	}
	else
	{
		int len;
		fd_set fdset;
		struct timeval timeout;

		if ( !stdin_active )
		{
			return NULL;
		}

		FD_ZERO(&fdset);
		FD_SET(0, &fdset);
		timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		if ( select(1, &fdset, NULL, NULL, &timeout) == -1 || !FD_ISSET(0, &fdset) )
		{
			return NULL;
		}

		len = read(0, text, sizeof(text));
		if ( len == 0 )
		{
			// eof!
			stdin_active = qfalse;
			return NULL;
		}

		if ( len < 1 )
		{
			return NULL;
		}
		text[len - 1] = 0; // rip off the /n and terminate

		return text;
	}
}

/*
========================================================================

EVENT LOOP

========================================================================
*/

#define MAX_QUED_EVENTS		256
#define MASK_QUED_EVENTS	( MAX_QUED_EVENTS - 1 )

static sysEvent_t eventQue[MAX_QUED_EVENTS];
static int eventHead = 0;
static int eventTail = 0;
static byte sys_packetReceived[MAX_MSGLEN];

void Sys_UnloadGame( void *dllHandle )
{
	const char *err;

	if ( !dllHandle )
	{
		Com_Printf("Sys_UnloadDll(NULL)\n");
		return;
	}

	dlclose(dllHandle);

	err = dlerror();
	if ( err )
	{
		Com_Printf("Sys_UnloadGame failed on dlclose: \"%s\"!\n", err);
	}
}

// no loading screen on the dedicated server
void Sys_LoadingKeepAlive()
{
}

// unreferenced dedicated-server stubs; original names unknown
void Sys_NullStub()
{
}

int Sys_NullQuery1()
{
	return 0;
}

int Sys_NullQuery2()
{
	return 0;
}

void Sys_OutOfMemErrorInternal( const char *filename, int line )
{
	fprintf(stderr, "OUT OF MEMORY! ABORTING!!! (%s:%d)\n", filename, line);
	exit(-1);
}

void Sys_UnableToLoadLibrary()
{
	Com_Error(ERR_FATAL, "Unable to load shared library\n");
}

void *Sys_LoadDll( const char *name, char *fqpath, int (**entryPoint)(int, ...), int systemcalls )
{
	void *libHandle;
	void (*dllEntry)(int);
	char fname[256];
	const char *pwdpath;
	const char *homepath;
	const char *basepath;
	const char *gamedir;
	char fn[256];
	char *err;

	err = NULL;
	*fqpath = 0;
	snprintf(fname, sizeof(fname), "%s.mp.i386.so", name);
	pwdpath = Sys_Cwd();
	homepath = Dvar_GetString("fs_homepath");
	basepath = Dvar_GetString("fs_basepath");
	gamedir = Dvar_GetString("fs_game");
	FS_BuildOSPath(pwdpath, gamedir, fname, fn);
	Com_Printf("Sys_LoadDll(%s)... ", fn);
	libHandle = dlopen(fn, RTLD_NOW);
	if ( !libHandle )
	{
		Com_Printf("failed\n");
		FS_BuildOSPath(homepath, gamedir, fname, fn);
		Com_Printf("Sys_LoadDll(%s)... ", fn);
		libHandle = dlopen(fn, RTLD_NOW);
		if ( !libHandle )
		{
			Com_Printf("failed\n");
			FS_BuildOSPath(basepath, gamedir, fname, fn);
			Com_Printf("Sys_LoadDll(%s)... ", fn);
			libHandle = dlopen(fn, RTLD_NOW);
			if ( !libHandle )
			{
				Com_Printf("\nSys_LoadDll(%s) failed:\n\"%s\"\n", fn, dlerror());
			}
			else
			{
				Com_Printf("ok\n");
			}
			if ( !libHandle )
			{
				Com_Error(ERR_FATAL, "Sys_LoadDll(%s) failed dlopen() completely!\n", name);
				return NULL;
			}
		}
		else
		{
			Com_Printf("ok\n");
		}
	}
	else
	{
		Com_Printf("ok\n");
	}
	I_strncpyz(fqpath, fn, MAX_QPATH);
	dllEntry = (void (*)(int))dlsym(libHandle, "dllEntry");
	*entryPoint = (int (*)(int, ...))dlsym(libHandle, "vmMain");
	if ( !*entryPoint || !dllEntry )
	{
		err = dlerror();
		Com_Error(ERR_FATAL, "Sys_LoadDll(%s) failed dlsym(vmMain):\n\"%s\" !\n", name, err);
		dlclose(libHandle);
		err = dlerror();
		if ( err )
		{
			Com_Printf("Sys_LoadDll(%s) failed dlcose:\n\"%s\"\n", name, err);
		}
		return NULL;
	}
	Com_Printf("Sys_LoadDll(%s) found **vmMain** at  %p  \n", name, *entryPoint);
	dllEntry(systemcalls);
	Com_Printf("Sys_LoadDll(%s) succeeded!\n", name);
	return libHandle;
}

// no background streaming thread on the dedicated server
void Sys_InitStreamThread()
{
}

void Sys_ShutdownStreamThread()
{
}

void Sys_BeginStreamedFile( fileHandle_t f, int readAhead )
{
}

void Sys_EndStreamedFile( fileHandle_t f )
{
}

int Sys_StreamedRead( void *buffer, int size, int count, fileHandle_t f )
{
	return FS_Read(buffer, size * count, f);
}

void Sys_StreamSeek( fileHandle_t f, int offset, int origin )
{
	FS_SeekInternal(f, offset, origin);
}

/*
================
Sys_QueEvent

A time of 0 will get the current time
Ptr should either be null, or point to a block of data that can
be freed by the game later.
================
*/
void Sys_QueEvent( int time, sysEventType_t type, int value, int value2, int ptrLength, void *ptr )
{
	sysEvent_t *ev;

	ev = &eventQue[eventHead & MASK_QUED_EVENTS];

	if ( eventHead - eventTail >= MAX_QUED_EVENTS )
	{
		Com_Printf("Sys_QueEvent: overflow\n");
		// we are discarding an event, but don't leak memory
		if ( ev->evPtr )
		{
			Z_Free(ev->evPtr);
		}
		eventTail++;
	}

	eventHead++;

	if ( time == 0 )
	{
		time = Sys_MilliSeconds();
	}

	ev->evTime = time;
	ev->evType = type;
	ev->evValue = value;
	ev->evValue2 = value2;
	ev->evPtrLength = ptrLength;
	ev->evPtr = ptr;
}

sysEvent_t Sys_GetEvent( void )
{
	sysEvent_t ev;
	char *s;
	msg_t netmsg;
	netadr_t adr;

	// return if we have data
	if ( eventHead > eventTail )
	{
		eventTail++;
		return eventQue[(eventTail - 1) & MASK_QUED_EVENTS];
	}

	// check for console commands
	s = Sys_ConsoleInput();
	if ( s )
	{
		char *b;
		int len;

		len = strlen(s) + 1;
		b = (char *)Z_Malloc(len);
		strcpy(b, s);
		Sys_QueEvent(0, SE_CONSOLE, 0, 0, len, b);
	}

	// check for network packets
	MSG_Init(&netmsg, sys_packetReceived, sizeof(sys_packetReceived));
	if ( Sys_GetPacket(&adr, &netmsg) )
	{
		netadr_t *buf;
		int len;

		// copy out to a seperate buffer for queueing
		len = sizeof(netadr_t) + netmsg.cursize;
		buf = (netadr_t *)Z_Malloc(len);
		*buf = adr;
		memcpy(buf + 1, netmsg.data, netmsg.cursize);
		Sys_QueEvent(0, SE_PACKET, 0, 0, len, buf);
	}

	// return if we have data
	if ( eventHead > eventTail )
	{
		eventTail++;
		return eventQue[(eventTail - 1) & MASK_QUED_EVENTS];
	}

	// create an empty event to return
	memset(&ev, 0, sizeof(ev));
	ev.evTime = Sys_MilliSeconds();

	return ev;
}

qboolean Sys_CheckCD()
{
	return qtrue;
}

void Sys_AppActivate()
{
}

char *Sys_GetClipboardData( void )
{
	return NULL;
}

void Sys_Print( const char *msg )
{
	if ( ttycon_on )
	{
		tty_Hide();
	}
	fputs(msg, stderr);
	if ( ttycon_on )
	{
		tty_Show();
	}
}

void Sys_ConfigureFPU()
{
	int current = 0;

	_FPU_GETCW(current);
}

void Sys_PrintBinVersion( const char *name )
{
	const char *date = BUILD_DATE;
	const char *time = BUILD_TIME;
	const char *sep = "==============================================================";

	fprintf(stdout, "\n\n%s\n", sep);
	fprintf(stdout, "Linux Quake3 Dedicated Server [%s %s]\n", date, time);
	fprintf(stdout, " local install: %s\n", name);
	fprintf(stdout, "%s\n\n", sep);
}

void Sys_Chmod( char *file, int mode )
{
	struct stat s_buf;
	int perm;

	if ( stat(file, &s_buf) )
	{
		Com_Printf("stat('%s')  failed: errno %d\n", file, errno);
		return;
	}
	perm = s_buf.st_mode | mode;
	if ( chmod(file, perm) )
	{
		Com_Printf("chmod('%s', %d) failed: errno %d\n", file, perm, errno);
	}
	Com_DPrintf("chmod +%d '%s'\n", file);
}

void Sys_DoStartProcess( char *cmdline )
{
	switch ( fork() )
	{
	case -1:
		break;
	case 0:
		if ( strchr(cmdline, ' ') )
		{
			system(cmdline);
		}
		else
		{
			execl(cmdline, cmdline, NULL);
		}
		_exit(0);
		break;
	}
}

void Sys_StartProcess( char *cmdline, qboolean doexit )
{
	if ( doexit )
	{
		Com_DPrintf("Sys_StartProcess %s (delaying to final exit)\n", cmdline);
		I_strncpyz(exit_cmdline, cmdline, sizeof(exit_cmdline));
		Cbuf_ExecuteText(EXEC_APPEND, "quit\n");
	}
	else
	{
		Com_DPrintf("Sys_StartProcess %s\n", cmdline);
		Sys_DoStartProcess(cmdline);
	}
}

void Sys_OpenURL( const char *url, qboolean doexit )
{
	const char *basepath;
	const char *homepath;
	const char *pwdpath;
	char fname[20];
	char fn[256];
	char cmdline[1024];

	Com_Printf("Sys_OpenURL %s\n", url);
	I_strncpyz(fname, "openurl.sh", 20);
	pwdpath = Sys_Cwd();
	Com_sprintf(fn, 256, "%s/%s", pwdpath, fname);
	if (access(fn, X_OK) == -1)
	{
		Com_DPrintf("%s not found\n", fn);
		homepath = Dvar_GetString("fs_homepath");
		Com_sprintf(fn, 256, "%s/%s", homepath, fname);
		if (access(fn, X_OK) == -1)
		{
			Com_DPrintf("%s not found\n", fn);
			basepath = Dvar_GetString("fs_basepath");
			Com_sprintf(fn, 256, "%s/%s", basepath, fname);
			if (access(fn, X_OK) == -1)
			{
				Com_DPrintf("%s not found\n", fn);
				Com_Printf("Can't find script '%s' to open requested URL (use +set developer 1 for more verbosity)\n", fname);
				return;
			}
		}
	}
	Com_DPrintf("URL script: %s\n", fn);
	Com_sprintf(cmdline, 1024, "%s '%s' &", fn, url);
	Sys_StartProcess(cmdline, doexit);
}

void Sys_ParseArgs( int argc, char *argv[] )
{
	if ( argc == 2 )
	{
		if ( !strcmp(argv[1], "--version") || !strcmp(argv[1], "-v") )
		{
			Sys_PrintBinVersion(argv[0]);
			Sys_Exit(0);
		}
	}
}

int main( int argc, char *argv[] )
{
	int len, i;
	char *cmdline;

	// go back to real user for config loads
	saved_euid = geteuid();
	seteuid(getuid());

	Com_SyncThreads();
	Sys_InitMainThread();
	Dvar_Init();
	Sys_ParseArgs(argc, argv);
	Sys_SetDefaultCDPath("");

	// merge the command line, this is kinda silly
	for ( len = 1, i = 1; i < argc; i++ )
	{
		len += strlen(argv[i]) + 1;
	}
	cmdline = new char[len];
	*cmdline = 0;
	for ( i = 1; i < argc; i++ )
	{
		if ( i > 1 )
		{
			strcat(cmdline, " ");
		}
		strcat(cmdline, argv[i]);
	}

	// clear queues
	memset(&eventQue[0], 0, MAX_QUED_EVENTS * sizeof(sysEvent_t));
	memset(&sys_packetReceived[0], 0, MAX_MSGLEN * sizeof(byte));

	Sys_MilliSeconds();
	Com_Init(cmdline);

	Sys_ConsoleInputInit();

	fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) | FNDELAY);

	while ( 1 )
	{
		Sys_ConfigureFPU();
		usleep(5000);
		Com_Frame();
	}
}

int Sys_LoadRenderer()
{
	Com_Error(ERR_FATAL, "Sys_LoadRenderer is unimplemented\n");
	return 0;
}

void Sys_UnloadRenderer()
{
	Com_Error(ERR_FATAL, "Sys_UnloadRenderer is unimplemented\n");
}

// Original name unknown; unreferenced.
static int unusedValue = 4986;
