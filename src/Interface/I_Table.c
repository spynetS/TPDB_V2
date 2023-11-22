#include <stdio.h>
#include <stdlib.h>
#include "I_Table.h"

TPTable *CreateTPTable(char *_Name, char *_Path)
{
	TPTable *newTPT = (TPTable*)malloc(sizeof(TPTable));
	newTPT->Name = _Name;
	newTPT->Path = _Path;
	newTPT->_ID  = -1;
	newTPT->ColumnTypes = NULL;
	newTPT->Rows = NULL;
}

void DestroyTPTable(TPTable *_self)
{
	free(_self->Name);
	_self->Name = NULL;
	free(_self->Path);
	_self->Path = NULL;
}
