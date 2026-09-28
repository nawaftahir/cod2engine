// build identification; original file name unknown
#include <stdio.h>

#define BUILD_NAME "pc_1.3_1_1"
#define BUILD_DATE "Mon May 01 2006 05:05:43PM"

// Original name unknown; size from the layout.
char buildInfo[128];

const char *getBuildNumber( void )
{
	sprintf(buildInfo, "%s %s", BUILD_NAME, BUILD_DATE);
	return buildInfo;
}
