#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MiscTools.h"

enum TP_ERROR_TYPES AppendToArrayOfPointers(void ***targetArray, size_t *targetArrayLength, void *ToAppend, size_t elementSize)
{
	void **RetArray = (void**)realloc(*targetArray, elementSize * ((*targetArrayLength) + 1));

	if (RetArray == NULL) {
		if (ENABLE_ERROR_LOG) {
			printf("%s\n", ERROR_ASCII_FAIL);
		}
		return TP_FAILED_AppendToArrayOfPointers;
	}

	RetArray[*targetArrayLength] = malloc(elementSize);
	if (RetArray[*targetArrayLength] == NULL) {
		free(RetArray);
		if (ENABLE_ERROR_LOG) {
			printf("%s\n", ERROR_ASCII_FAIL);
		}
		return TP_FAILED_AppendToArrayOfPointers;
	}

	memcpy(RetArray[*targetArrayLength], ToAppend, elementSize);

	(*targetArrayLength)++;
	*targetArray = RetArray;

	if (ENABLE_ERROR_LOG) {
		printf("%s:", ERROR_ASCII_SUCCESS);
	}
	return TP_SUCCESS;
}
