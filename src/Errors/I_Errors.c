#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "I_Errors.h"

void TP_CheckError(enum TP_ERROR_TYPES err)
{
	if(err != TP_SUCCESS)
	{
		int ErrorDocLinkSize = snprintf(NULL, 0, "firefox https://techpology.github.io/TPDB_V2/Errors/TPErrors.html?%d", err) + 1;
		char *ErrorDocLink = (char*)malloc(sizeof(char) * ErrorDocLinkSize);
		sprintf(ErrorDocLink, "firefox https://techpology.github.io/TPDB_V2/Errors/TPErrors.html?%d", err);

		puts("You can enable auto redirect within the source code in:\n{/src/Errors/I_Errors.c : (TP_CheckError())}, uncomment system(...)");
		puts(ErrorDocLink);
		//system(ErrorDocLink);
		free(ErrorDocLink);
		exit(err);
	}
}
