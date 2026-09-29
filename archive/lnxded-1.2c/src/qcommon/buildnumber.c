// build identification; original file name unknown
#include <stdio.h>

#define BUILD_NUMBER 696
#define BUILD_DATE   "Apr 19 2006"
#define BUILD_TIME   "20:44:22"

// Original name unknown; size from the layout.
char buildInfo[1024];

const char *getBuildNumber( void )
{
	sprintf(buildInfo, "%d %s %s", BUILD_NUMBER, BUILD_DATE, BUILD_TIME);
	return buildInfo;
}
