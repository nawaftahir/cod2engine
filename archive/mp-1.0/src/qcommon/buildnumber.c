// build identification; original file name unknown
#include <stdio.h>
/* 20 unused symbols, no code or data. The retail link had more global symbols here, and the
   optimizer's choices in later functions depend on that count. */
static int bn_pad_0;
static int bn_pad_1;
static int bn_pad_2;
static int bn_pad_3;
static int bn_pad_4;
static int bn_pad_5;
static int bn_pad_6;
static int bn_pad_7;
static int bn_pad_8;
static int bn_pad_9;
static int bn_pad_10;
static int bn_pad_11;
static int bn_pad_12;
static int bn_pad_13;
static int bn_pad_14;
static int bn_pad_15;
static int bn_pad_16;
static int bn_pad_17;
static int bn_pad_18;
static int bn_pad_19;

#define BUILD_NUMBER "crc6_v1"
#define BUILD_TIME   "Thu Oct 06 2005 07:13:42PM"

// Mac STABS buf[128]; retail .data ends 128 bytes after this buffer.
char buildInfo[128];

const char *getBuildNumber( void )
{
	sprintf(buildInfo, "%s %s", BUILD_NUMBER, BUILD_TIME);
	return buildInfo;
}
