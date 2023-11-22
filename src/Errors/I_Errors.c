#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "I_Errors.h"

void TP_CheckError(enum TP_ERROR_TYPES err)
{
	int ErrorDocLinkSize = snprintf(NULL, 0, "firefox ./docs/Errors/TPErrors.html?%d", err) + 1;
	char *ErrorDocLink = (char*)malloc(sizeof(char) * ErrorDocLinkSize);
	sprintf(ErrorDocLink, "firefox ./docs/Errors/TPErrors.html?%d", err);

	system(ErrorDocLink);
	free(ErrorDocLink);
}
