#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Storage/Storage.h"
#include "../Utils/StringTools.h"
#include "../Utils/MISCTools.h"
#include "I_Database.h"
#include "I_Table.h"

TPDatabase *CreateTPDatabase(char *_Name, char *_Path)
{
	TPDatabase *newTPDB = (TPDatabase*)malloc(sizeof(TPDatabase));
	newTPDB->Name = strdup(_Name);
	newTPDB->Path = strdup(_Path);
	newTPDB->ConfigPath = TP_StrnCat(_Path, 1, "/Config");
	newTPDB->_ID = 0;
	newTPDB->TablesCount = 0;
	newTPDB->Tables = NULL;

	TP_CheckError(TP_Mkdir(newTPDB->Path), TP_IGNORE);
	TP_CheckError(TP_Mkdir(newTPDB->ConfigPath), TP_IGNORE);
	return newTPDB;
}

void DestroyTPDatabase(TPDatabase *_self)
{
	if(_self != NULL)
	{
		if(_self->Tables != NULL)
		{
			for (int i = 0; i < _self->TablesCount; i++)
			{
				DestroyTPTable(_self->Tables[i]);
			}
			free(_self->Tables);
		}
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

enum TP_ERROR_TYPES AddTable(TPDatabase *_self, char *_Name)
{
	char *_path = TP_StrnCat("/", 1, _Name);
	TPTable *newTbl = CreateTPTable(_path, _self, TP_FALSE);
	free(_path);

	//AppendToArrayOfPointers((void***)&_self->Tables, &_self->TablesCount, newTbl, sizeof(TPTable*));
	_self->Tables = realloc(_self->Tables, sizeof(TPTable*) * (_self->TablesCount + 1));
	_self->Tables[_self->TablesCount] = newTbl;
	_self->TablesCount++;

	if(_self->Tables != NULL)
	{
		return TP_SUCCESS;
	}
	else
	{
		return TP_FAILED_AddTable;
	}
}
