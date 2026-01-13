#include "minilog.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int init(const char *dir, const char *file)
{
	int dftfd = 1; //stdout
	struct stat statbuf;
	char *fullname = NULL;

	if (stat(dir, &statbuf) == -1)
	{
		switch (errno)
		{
		case EFAULT:
		case ELOOP:
		case ENAMETOOLONG:
		case ENOENT:
		case ENOTDIR:
			fprintf(stderr, "%s is unreachable\n", dir);
			return CANNOT_REACH;
		case ENOMEM:
			fprintf(stderr, "Kernel is out of memory!\n");
			return NO_MEMORY;
		default:
			if (mkdir(dir, 0775) == -1)
			{
				fprintf(stderr, "Failed to create %s\n", dir);
				return CANNOT_MKDIR;
			}
		}
	}
	fullname = calloc(strlen(dir) + strlen(file) + 2, sizeof (char));
	if (fullname == NULL)
	{
		fprintf(stderr, "No memory for full name buffer\n");
		return CANNOT_NAME;
	}
	strcpy(fullname, dir);
	strcat(fullname, "/");
	strcat(fullname, file);
	if (open(fullname, O_CREAT|O_APPEND, 0666) == -1)
	{
		fprintf(stderr, "Failed to open %s, error %i\n", file, errno);
		return CANNOT_OPEN;
	}
}
