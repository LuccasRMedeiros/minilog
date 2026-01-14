#ifndef MINILOG_H
#define MINILOG_H

#include <stdio.h>

#define SUCCESS			0
#define CANNOT_REACH 	-1
#define NO_MEMORY 		-2
#define CANNOT_MKDIR 	-3
#define CANNOT_NAME		-4
#define CANNOT_OPEN		-5
#define CANNOT_REDIRECT	-6

int init(const char *dir, const char *file);

#endif // MINILOG_H
