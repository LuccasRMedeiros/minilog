#include "minilog.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int init(const char *dir, const char *file)
{
	int logfd = 1; //stdout
	int dirfd = 0;
	struct stat statbuf;

	if (stat(dir, &statbuf) < 0)
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
			if (mkdir(dir, 0775) < 0)
			{
				fprintf(stderr, "Failed to create %s\n", dir);
				return CANNOT_MKDIR;
			}
		}
	}
	dirfd = open(dir, O_RDONLY|O_DIRECTORY);
	if (dirfd < 0)
	{
		fprintf(stderr, "%s is unreachable, error %i\n", dir, errno);
		return CANNOT_REACH;
	}
	logfd = openat(dirfd, file, O_CREAT|O_APPEND, 0666);
	if (logfd < 0)
	{
		fprintf(stderr, "Failed to open %s, error %i\n", file, errno);
		return CANNOT_OPEN;
	}
	if (dup2(logfd, STDOUT_FILENO) < 0)
	{
		fprintf(
				stderr,
				"Failed to redirect output to file %s/%s, error %i\n",
				dir,
				file,
				errno);
		close(dirfd);
		close(logfd);
		return CANNOT_REDIRECT;
	}
	close(dirfd);
	close(logfd);
	return SUCCESS;
}
