#include <string.h>

// The statistics overlay; its warnings are drawn by the client only, so the server keeps the storage.
struct Material;

struct statmonitor_s
{
	int endtime;
	Material *material;
};

static statmonitor_s stats[7];
static int statCount;

void StatMon_Warning(int type, int duration, const char *materialName)
{
}

void StatMon_GetStatsArray(const statmonitor_s **array, int *count)
{
	*array = stats;
	*count = statCount;
}

void StatMon_Reset(void)
{
	memset(stats, 0, sizeof(stats));
	statCount = 0;
}
