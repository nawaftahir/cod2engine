#include <pthread.h>

#include "../qcommon/qcommon.h"
#include "linux_local.h"

static void *g_threadValues[THREAD_VALUE_COUNT];
// unreferenced in this build
static threadid_t unusedThreadId;
static threadid_t mainthread;
// Unreferenced storage; original declarations unknown (sized from the layout).
static int threads_unreferenced;

void Sys_InitMainThread()
{
	mainthread = pthread_self();
	Com_InitThreadData(THREAD_CONTEXT_MAIN);
}

// unreferenced; original name unknown
int Sys_NullQuery4( void )
{
	return 0;
}

qboolean Sys_IsMainThread( void )
{
	threadid_t id;

	id = pthread_self();
	id = id == mainthread;
	return id;
}

void Sys_SetValue( int valueIndex, void *data )
{
	g_threadValues[valueIndex] = data;
}

void *Sys_GetValue( int valueIndex )
{
	return g_threadValues[valueIndex];
}
