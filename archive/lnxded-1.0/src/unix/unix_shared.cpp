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
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <pwd.h>
#include <math.h>

#include "../qcommon/qcommon.h"
#include "linux_local.h"

// Used to determine CD Path
static char cdPath[MAX_OSPATH];

// Used to determine local installation path
static char installPath[MAX_OSPATH];

// Used to determine where to store user-specific files
static char homePath[MAX_OSPATH];

// current time in ms, using sys_timeBase as origin
static int curtime;
// base time in seconds, that's our origin
static unsigned long sys_timeBase = 0;

int Sys_Milliseconds( void )
{
	struct timeval tp;
	struct timezone tzp;

	gettimeofday(&tp, &tzp);

	if ( !sys_timeBase )
	{
		sys_timeBase = tp.tv_sec;
		return tp.tv_usec / 1000;
	}

	curtime = (tp.tv_sec - sys_timeBase) * 1000 + tp.tv_usec / 1000;

	return curtime;
}

// wall-clock milliseconds since the Epoch
int Sys_MillisecondsRaw( void )
{
	struct timeval tp;
	struct timezone tzp;

	gettimeofday(&tp, &tzp);
	curtime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	return curtime;
}

long fastftol( float f )
{
	return (long)f;
}

void Sys_SnapVector( float *v )
{
	v[0] = rint(v[0]);
	v[1] = rint(v[1]);
	v[2] = rint(v[2]);
}

void Sys_Mkdir( const char *path )
{
	mkdir(path, 0777);
}

#define MAX_FOUND_FILES 0x1000

void Sys_ListFilteredFiles( const char *basedir, const char *subdirs, const char *filter, char **list, int *numfiles )
{
	char search[MAX_OSPATH], newsubdirs[MAX_OSPATH];
	char filename[MAX_OSPATH];
	DIR *fdir;
	struct dirent *d;
	struct stat st;

	if ( *numfiles >= MAX_FOUND_FILES - 1 )
	{
		return;
	}

	if ( strlen(subdirs) )
	{
		Com_sprintf(search, sizeof(search), "%s/%s", basedir, subdirs);
	}
	else
	{
		Com_sprintf(search, sizeof(search), "%s", basedir);
	}

	if ( (fdir = opendir(search)) == NULL )
	{
		return;
	}

	while ( (d = readdir(fdir)) != NULL )
	{
		Com_sprintf(filename, sizeof(filename), "%s/%s", search, d->d_name);
		if ( stat(filename, &st) == -1 )
		{
			continue;
		}

		if ( st.st_mode & S_IFDIR )
		{
			if ( I_stricmp(d->d_name, ".") && I_stricmp(d->d_name, "..") )
			{
				if ( strlen(subdirs) )
				{
					Com_sprintf(newsubdirs, sizeof(newsubdirs), "%s/%s", subdirs, d->d_name);
				}
				else
				{
					Com_sprintf(newsubdirs, sizeof(newsubdirs), "%s", d->d_name);
				}
				Sys_ListFilteredFiles(basedir, newsubdirs, filter, list, numfiles);
			}
		}
		if ( *numfiles >= MAX_FOUND_FILES - 1 )
		{
			break;
		}
		Com_sprintf(filename, sizeof(filename), "%s/%s", subdirs, d->d_name);
		if ( !Com_FilterPath(filter, filename, qfalse) )
		{
			continue;
		}
		list[*numfiles] = CopyString(filename);
		(*numfiles)++;
	}

	closedir(fdir);
}

char **Sys_ListFiles( const char *directory, const char *extension, const char *filter, int *numfiles, qboolean wantsubs )
{
	struct dirent *d;
	DIR *fdir;
	qboolean dironly = wantsubs;
	char search[MAX_OSPATH];
	int nfiles;
	char **listCopy;
	char *list[MAX_FOUND_FILES];
	int i;
	struct stat st;
	int extLen;

	if ( filter )
	{
		nfiles = 0;
		Sys_ListFilteredFiles(directory, "", filter, list, &nfiles);

		list[nfiles] = 0;
		*numfiles = nfiles;

		if ( !nfiles )
		{
			return NULL;
		}

		listCopy = (char **)Z_Malloc((nfiles + 1) * sizeof(*listCopy));
		for ( i = 0; i < nfiles; i++ )
		{
			listCopy[i] = list[i];
		}
		listCopy[i] = NULL;

		return listCopy;
	}

	if ( !extension )
	{
		extension = "";
	}

	if ( extension[0] == '/' && extension[1] == 0 )
	{
		extension = "";
		dironly = qtrue;
	}

	extLen = strlen(extension);

	// search
	nfiles = 0;

	if ( (fdir = opendir(directory)) == NULL )
	{
		*numfiles = 0;
		return NULL;
	}

	while ( (d = readdir(fdir)) != NULL )
	{
		Com_sprintf(search, sizeof(search), "%s/%s", directory, d->d_name);
		if ( stat(search, &st) == -1 )
		{
			continue;
		}
		if ( (dironly && !(st.st_mode & S_IFDIR)) || (!dironly && (st.st_mode & S_IFDIR)) )
		{
			continue;
		}

		if ( *extension )
		{
			if ( strlen(d->d_name) < strlen(extension)
				|| I_stricmp(d->d_name + strlen(d->d_name) - strlen(extension), extension) )
			{
				continue; // didn't match
			}
		}

		if ( nfiles == MAX_FOUND_FILES - 1 )
		{
			break;
		}
		list[nfiles] = CopyString(d->d_name);
		nfiles++;
	}

	list[nfiles] = 0;

	closedir(fdir);

	// return a copy of the list
	*numfiles = nfiles;

	if ( !nfiles )
	{
		return NULL;
	}

	listCopy = (char **)Z_Malloc((nfiles + 1) * sizeof(*listCopy));
	for ( i = 0; i < nfiles; i++ )
	{
		listCopy[i] = list[i];
	}
	listCopy[i] = NULL;

	return listCopy;
}

void Sys_FreeFileList( char **list )
{
	int i;

	if ( !list )
	{
		return;
	}

	for ( i = 0; list[i]; i++ )
	{
		Z_Free(list[i]);
	}

	Z_Free(list);
}

char *Sys_Cwd( void )
{
	static char cwd[MAX_OSPATH];

	getcwd(cwd, sizeof(cwd) - 1);
	cwd[MAX_OSPATH - 1] = 0;

	return cwd;
}

void Sys_SetDefaultCDPath( const char *path )
{
	I_strncpyz(cdPath, path, sizeof(cdPath));
}

const char *Sys_DefaultCDPath( void )
{
	return cdPath;
}

char *Sys_DefaultBasePath( void )
{
	if ( *installPath )
	{
		return installPath;
	}
	else
	{
		return Sys_Cwd();
	}
}

void Sys_SetDefaultInstallPath( const char *path )
{
	I_strncpyz(installPath, path, sizeof(installPath));
}

char *Sys_DefaultInstallPath( void )
{
	if ( *installPath )
	{
		return installPath;
	}
	else
	{
		return Sys_Cwd();
	}
}

void Sys_SetDefaultHomePath( const char *path )
{
	I_strncpyz(homePath, path, sizeof(homePath));
}

const char *Sys_DefaultHomePath( void )
{
	char *p;

	if ( *homePath )
	{
		return homePath;
	}

	if ( (p = getenv("HOME")) != NULL )
	{
		I_strncpyz(homePath, p, sizeof(homePath));
		I_strncat(homePath, sizeof(homePath), "/.callofduty2");
		if ( mkdir(homePath, 0777) )
		{
			if ( errno != EEXIST )
			{
				Sys_Error("Unable to create directory \"%s\", error is %s(%d)\n", homePath, strerror(errno), errno);
			}
		}
		return homePath;
	}
	return ""; // assume current dir
}

int Sys_GetProcessorId( void )
{
	return CPUID_GENERIC;
}

// unreferenced; original name unknown
int Sys_NullQuery3( void )
{
	return 0;
}

void Sys_ShowConsole( int visLevel, qboolean quitOnClose )
{
}

const char *Sys_GetCurrentUser( void )
{
	struct passwd *p;

	if ( (p = getpwuid(getuid())) == NULL )
	{
		return "player";
	}
	return p->pw_name;
}

char *strlwr( char *s )
{
	if ( s == NULL )
	{
		return s;
	}
	while ( *s )
	{
		*s = tolower(*s);
		s++;
	}
	return s;
}

qboolean Sys_DirectoryHasContents( const char *dir )
{
	char *path;
	int result;
	DIR *hdir;
	struct dirent *hfile;

	path = new char[strlen(dir) + 1];
	strcpy(path, dir);
	for ( result = 0; path[result]; result++ )
	{
		if ( path[result] == '\\' )
		{
			path[result] = '/';
		}
	}

	result = 0;
	hdir = opendir(path);
	if ( hdir )
	{
		while ( 1 )
		{
			hfile = readdir(hdir);
			if ( !hfile )
			{
				break;
			}
			if ( !strcmp(hfile->d_name, ".") )
			{
				continue;
			}
			if ( !strcmp(hfile->d_name, "..") )
			{
				continue;
			}
			result = 1;
			break;
		}
		closedir(hdir);
	}

	delete[] path;

	return result;
}

int Sys_RemoveDirTree(const char *dir)
{
	char *path;
	int result;
	DIR *hdir;
	struct dirent *hfile;
	size_t len;
	char *filename;
	struct stat info;

	path = new char[strlen(dir) + 1];
	strcpy(path, dir);
	for (result = 0; path[result]; result++)
	{
		if (path[result] == '\\')
			path[result] = '/';
	}
	result = 1;
	hdir = opendir(path);
	if (hdir)
	{
		while (1)
		{
			hfile = readdir(hdir);
			if (!hfile)
				break;
			if (!strcmp(hfile->d_name, "."))
				continue;
			if (!strcmp(hfile->d_name, ".."))
				continue;
			len = strlen(path) + strlen(hfile->d_name) + 2;
			filename = new char[len];
			snprintf(filename, len, "%s/%s", path, hfile->d_name);
			if (stat(filename, &info) == -1)
				result = 0;
			else if (S_ISDIR(info.st_mode))
				result = Sys_RemoveDirTree(filename);
			else
				result = unlink(filename) != -1;
			delete[] filename;
			if (!result)
				break;
		}
		closedir(hdir);
	}
	if (result == 1)
		result = rmdir(path) != -1;
	delete[] path;
	return 1;
}
