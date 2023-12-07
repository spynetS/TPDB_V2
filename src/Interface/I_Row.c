#include <stdio.h>
#include <stdlib.h>

#include "../Errors/I_Errors.h"
#include "../Utils/StringTools.h"
#include "../Storage/Storage.h"
#include "I_Row.h"

TPTable_Row *CreateTPTableRow(int __ID, TPTable *_Table)
{
	TPTable_Row *newTPTR = (TPTable_Row*)malloc(sizeof(TPTable_Row));
	newTPTR->_ID = __ID;
	newTPTR->ValCount = _Table->ColCount;
	newTPTR->Values = (char**)malloc(sizeof(char*) * (newTPTR->ValCount));

	for (int i = 0; i < newTPTR->ValCount; i++)
	{
		newTPTR->Values[i] = NULL;
	}

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
				if(_self->Values[i] != NULL)
				{
					free(_self->Values[i]);
					_self->Values[i] = NULL;
				}
			}
			free(_self->Values);
		}
		free(_self);
	}
}

void EmptyRowValues(TPTable_Row *_self)
{
	if(_self != NULL)
	{
		if(_self->Values != NULL)
		{
			for (int i = 0; i < _self->ValCount; i++)
			{
				if(_self->Values[i] != NULL)
				{
					free(_self->Values[i]);
					_self->Values[i] = NULL;
				}
			}
		}
	}
}

enum TP_ERROR_TYPES UpdateRow(TPTable *_parent, TPTable_Row *_self)
{
	char *ToStore 	= TP_StrnCatArray(_self->Values, _self->ValCount, ";");
	if(ToStore == NULL){ return TP_FAILED_UPDATEROW; }

	size_t idSize	= snprintf(NULL, 0, "/%d", _self->_ID) + 1;
	char *idStr		= (char*) malloc(sizeof(char) * idSize);
	sprintf(idStr, "/%d", _self->_ID);
	if(idStr == NULL){ return TP_FAILED_UPDATEROW; }

	char *Path		= TP_StrnCat(_parent->Path, 2, idStr, TP_ROW_EXT);
	if(Path == NULL){ return TP_FAILED_UPDATEROW; }
	TP_StoreFile(Path, ToStore);

	free(idStr);
	free(Path);
	free(ToStore);
	if(_parent->RowsOnDemand == TP_TRUE){ EmptyRowValues(_self); }
	return TP_SUCCESS;
}
