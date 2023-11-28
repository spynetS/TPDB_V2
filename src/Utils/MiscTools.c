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

enum TP_ERROR_TYPES FreeArrayOfPointers(void ***targetArray, size_t targetArrayLength)
{
	if((*targetArray) != NULL)
	{
		for (size_t i = 0; i < targetArrayLength; i++)
		{
			if((*targetArray)[i] != NULL)
			{
				free((*targetArray)[i]);
				(*targetArray)[i] = NULL;
			}
			else
			{
				return TP_FAILED_FreeArrayOfPointers;
			}
		}
		free((*targetArray));
		(*targetArray) = NULL;
		return TP_SUCCESS;
	}
	else
	{
		return TP_FAILED_FreeArrayOfPointers;
	}
}

/* enum TP_ERROR_TYPES AppendToArrayOfPointers(void ***targetArray, size_t *targetArrayLength, void *ToAppend, size_t elementSize)
{
    void **newArray = NULL;

    if ((*targetArray) == NULL)
    {
        newArray = malloc(elementSize);
    }
    else
    {
        newArray = realloc((*targetArray), elementSize * ((*targetArrayLength) + 1));
    }

    if (newArray == NULL)
    {
        return TP_FAILED_AppendToArrayOfPointers; // Allocation failure
    }

    // Copy the new element
    memcpy(newArray[*targetArrayLength], ToAppend, elementSize);

    // Update the array and length
    *targetArray = newArray;
    (*targetArrayLength)++;

    return TP_SUCCESS;
}
 */