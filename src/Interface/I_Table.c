#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Utils/StringTools.h"
#include "I_Table.h"

TPTable *CreateTPTable(char *_Name, TPDatabase *_Database)
{
	TPTable *newTPT = (TPTable*)malloc(sizeof(TPTable));
	newTPT->ParentDatabase = _Database;
	
	newTPT->_ID  = -1;
	newTPT->Name = strdup(_Name);
	newTPT->Path = TP_StrnCat(_Database->Path, 1, newTPT->Name);

	newTPT->ColumnTypes = NULL;
	newTPT->Rows = NULL;

	return newTPT;
}

void DestroyTPTable(TPTable *_self)
{
	if(_self != NULL)
	{
		if(_self->Name != NULL)
		{
			free(_self->Name);
			_self->Name = NULL;
		}
		if(_self->Path != NULL)
		{
			free(_self->Path);
			_self->Path = NULL;
		}
		free(_self);
	}
}
