#include <stdio.h>
#include <stdlib.h>
#include "I_Row.h"

TPTable_Row *CreateTPTableRow(int __ID, int _ValCount)
{
	TPTable_Row *newTPTR = (TPTable_Row*)malloc(sizeof(TPTable_Row));
	newTPTR->_ID = __ID;
	newTPTR->ValCount = _ValCount;
	newTPTR->Values = NULL;

	return newTPTR;
}

void DestroyTPTableRow(TPTable_Row *_self)
{
	_self->_ID = -1;
	for (int i = 0; i < _self->ValCount; i++)
	{
		free(_self->Values[i]);
	}
	free(_self->Values);
	_self->ValCount = -1;
}
