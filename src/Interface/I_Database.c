#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "I_Database.h"

TPDatabase *CreateTPDatabase(char *_Name, char *_Path)
{
	TPDatabase *newTPDB = (TPDatabase*)malloc(sizeof(TPDatabase));
	newTPDB->Name = strdup(_Name);
	newTPDB->Path = strdup(_Path);
	newTPDB->_ID = 0;
	newTPDB->Tables = NULL;
	return newTPDB;
}

void DestroyTPDatabase(TPDatabase *_self)
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
