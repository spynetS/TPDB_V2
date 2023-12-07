#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "SerializeTools.h"

char *SERIALIZE_Int_Str(int a)
{
	size_t aSize = snprintf(NULL, 0, "%d", a) + 1;
	char *ret = (char*)malloc(sizeof(char) * aSize);
	sprintf(ret, "%d", a);
	return ret;
}

char *SERIALIZE_Float_Str(float a)
{
	size_t aSize = snprintf(NULL, 0, "%f", a) + 1;
	char *ret = (char*)malloc(sizeof(char) * aSize);
	sprintf(ret, "%f", a);
	return ret;
}

char *SERIALIZE_Char_Str(char a)
{
	size_t aSize = snprintf(NULL, 0, "%c", a) + 1;
	char *ret = (char*)malloc(sizeof(char) * aSize);
	sprintf(ret, "%c", a);
	return ret;
}

char *SERIALIZE_Fkey_Str(TPForeignKey *a)
{
	size_t aSize = snprintf(NULL, 0, "%s:%d", a->TableName, a->_ID) + 1;
	char *ret = (char*)malloc(sizeof(char) * aSize);
	sprintf(ret, "%s:%d", a->TableName, a->_ID);
	return ret;
}

char *SERIALIZE_RowID_Path(TPTable *_tbl, int _id)
{
	size_t retSize = snprintf(NULL, 0, "%s/%d.tdf", _tbl->Path, _id) + 1;
	char *ret = (char*)malloc(sizeof(char) * retSize);
	sprintf(ret, "%s/%d.tdf", _tbl->Path, _id);
	return ret;
}
