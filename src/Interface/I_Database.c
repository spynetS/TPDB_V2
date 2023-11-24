#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Storage/Storage.h"
#include "../Utils/StringTools.h"
#include "I_Database.h"

TPDatabase *CreateTPDatabase(char *_Name, char *_Path)
{
	TPDatabase *newTPDB = (TPDatabase*)malloc(sizeof(TPDatabase));
	newTPDB->Name = strdup(_Name);
	newTPDB->Path = strdup(_Path);
	newTPDB->ConfigPath = TP_StrnCat(_Path, 1, "/Config");
	newTPDB->_ID = 0;
	newTPDB->Tables = NULL;

	TP_CheckError(TP_Mkdir(newTPDB->Path), TP_IGNORE);
	TP_CheckError(TP_Mkdir(newTPDB->ConfigPath), TP_IGNORE);
	return newTPDB;
}

void DestroyTPDatabase(TPDatabase *_self)
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
		if(_self->ConfigPath != NULL)
		{
			free(_self->ConfigPath);
			_self->ConfigPath = NULL;
		}
		free(_self);
	}
}
