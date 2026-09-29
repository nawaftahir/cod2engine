#include <string.h>
#include <dirent.h>

// true when a directory holds anything besides "." and ".."
int Sys_DirectoryHasEntries( const char *dir )
{
	DIR *hdir;
	struct dirent *hfiles;
	int result;

	result = 0;
	hdir = opendir(dir);
	if ( !hdir )
	{
		return 0;
	}
	while ( 1 )
	{
		hfiles = readdir(hdir);
		if ( !hfiles )
		{
			break;
		}
		if ( !strcmp(hfiles->d_name, ".") || !strcmp(hfiles->d_name, "..") )
		{
			continue;
		}
		result = 1;
		break;
	}
	closedir(hdir);
	return result;
}
