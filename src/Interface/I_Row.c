#include <stdio.h>
#include <stdlib.h>
#include "I_Row.h"

TPTable_Row *CreateTPTableRow(int __ID, TPTable *_Table)
{
	TPTable_Row *newTPTR = (TPTable_Row*)malloc(sizeof(TPTable_Row));
	newTPTR->_ID = __ID;
	newTPTR->ValCount = _Table->ColCount;
	newTPTR->Values = NULL;

	return newTPTR;
}

void DestroyTPTableRow(TPTable_Row *_self)
{
	if(_self != NULL)
	{
		_self->_ID = -1;

		if(_self->Values != NULL)
		{
			for (int i = 0; i < _self->ValCount; i++)
			{
				free(_self->Values[i]);
			}
			free(_self->Values);
		}
		
		free(_self);
	}
}
