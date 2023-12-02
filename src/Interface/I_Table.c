#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Utils/StringTools.h"
#include "../Utils/SerializeTools.h"
#include "I_Table.h"
#include "I_Row.h"

TPTable *CreateTPTable(char *_Name, TPDatabase *_Database, int _lazyLoadRows)
{
	TPTable *newTPT = (TPTable*)malloc(sizeof(TPTable));
	newTPT->ParentDatabase = _Database;
	
	newTPT->_ID  = -1;
	newTPT->Name = strdup(_Name);
	newTPT->Path = TP_StrnCat(_Database->Path, 1, newTPT->Name);

	newTPT->ColumnTypes = NULL;
	
	newTPT->ColCount = 0;
	newTPT->RowCount = 0;

	newTPT->Rows = NULL;
	newTPT->RowsOnDemand = _lazyLoadRows;

	return newTPT;
}

void DestroyTPTable(TPTable *_self)
{
	if(_self != NULL)
	{
		if(_self->Rows != NULL)
		{
			for (int i = 0; i < _self->RowCount; i++)
			{
				DestroyTPTableRow(_self->Rows[i]);
			}
			free(_self->Rows);
		}
		if(_self->ColumnTypes != NULL)
		{
			free(_self->ColumnTypes);
			_self->ColCount = 0;
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
		_self->ParentDatabase = NULL;
		free(_self);
	}
}

enum TP_ERROR_TYPES SetColumnTypes(TPTable *_self, int _count, ...)
{
	_self->ColumnTypes = (enum TPTable_Column_Types*)malloc(sizeof(enum TPTable_Column_Types) * _count);
	if(_self->ColumnTypes == NULL)
	{
		return TP_FAILED_SetColumnTypes;
	}

	va_list args;
	va_start(args, _count);

	for (int i = 0; i < _count; i++)
	{
		_self->ColumnTypes[i] = va_arg(args, enum TPTable_Column_Types);
	}
	va_end(args);
	_self->ColCount = _count;
	return TP_SUCCESS;
}

enum TP_ERROR_TYPES AddRow(TPTable *_self, int _count, ...)
{
	if(_self->ColumnTypes == NULL || _self->ColCount <= 0){ return TP_FAILED_AddRow; }
	_self->Rows = realloc(_self->Rows, sizeof(TPTable_Row) * (_self->RowCount + 1));
	_count = _self->ColCount;

	if(_self->Rows != NULL)
	{
		_self->Rows[_self->RowCount] = CreateTPTableRow(_self->RowCount, _self);
		_self->RowCount++;
	}
	else
	{
		return TP_FAILED_AddRow;
	}

	va_list args;
	va_start(args, _count);

	for (int i = 0; i < _self->ColCount; i++)
	{
		switch (_self->ColumnTypes[i])
		{
			case TP_INT:
				int _int = va_arg(args, int);
				_self->Rows[_self->RowCount - 1]->Values[i] = SERIALIZE_Int_Str(_int);
				break;
			case TP_FLOAT:
				double _float = va_arg(args, double);
				_self->Rows[_self->RowCount - 1]->Values[i] = SERIALIZE_Float_Str(_float);
				break;
			case TP_CHAR:
				unsigned char _char = (unsigned char)va_arg(args, int);
				_self->Rows[_self->RowCount - 1]->Values[i] = SERIALIZE_Char_Str(_char);
				break;
			case TP_FKEY:
				TPForeignKey* _TPForeignKey = va_arg(args, TPForeignKey*);
				_self->Rows[_self->RowCount - 1]->Values[i] = SERIALIZE_Fkey_Str(_TPForeignKey);
				break;
			default:
				char *_charp = va_arg(args, char*);
				_self->Rows[_self->RowCount - 1]->Values[i] = strdup(_charp);
				break;
		}
	}
	va_end(args);

	UpdateRow(_self, _self->Rows[_self->RowCount - 1]);
	return TP_SUCCESS;
}
