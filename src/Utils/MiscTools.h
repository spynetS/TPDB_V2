#ifndef MISCTOOLS_H
#define MISCTOOLS_H

#include "../Errors/I_Errors.h"

enum TP_ERROR_TYPES AppendToArrayOfPointers(void ***targetArray, size_t *targetArrayLength, void *ToAppend, size_t elementSize);

#endif