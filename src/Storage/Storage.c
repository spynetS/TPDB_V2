#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Storage.h"
#include "../Errors/I_Errors.h"

enum TP_ERROR_TYPES TP_Mkdir(char *_path)
{
	if(ENABLE_ERROR_LOG){ printf("--|TP_TEST_Mkdir|--: ..."); }

	if(mkdir(_path, 0700) == -1)
	{
		if(ENABLE_ERROR_LOG){ printf("%s\n", ERROR_ASCII_WARNING); }
		return TP_FAILED_MKDIR;
	}

	if(ENABLE_ERROR_LOG){ printf("%s\n", ERROR_ASCII_SUCCESS); }
	return TP_SUCCESS;
}
