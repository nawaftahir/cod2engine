// build identification; original file name unknown
#include <stdio.h>

#define BUILD_NUMBER "pc_1.3_1_1"
#define BUILD_TIME   "Mon May 01 2006 05:05:43PM"

// Mac STABS buf[128]; retail .data ends 128 bytes after this buffer.
char buildInfo[128];

const char *getBuildNumber( void )
{
	sprintf(buildInfo, "%s %s", BUILD_NUMBER, BUILD_TIME);
	return buildInfo;
}
