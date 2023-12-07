#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "SerializeTools.h"
#include "StringTools.h"

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
	size_t aSize = snprintf(NULL, 0, "%d:%d", a->TableId, a->_ID) + 1;
	char *ret = (char*)malloc(sizeof(char) * aSize);
	sprintf(ret, "%d:%d", a->TableId, a->_ID);
	return ret;
}

int *SERIALIZE_Str_Int(char *str)
{
	int *intValue = (int*) malloc(sizeof(int));
	(*intValue) = atoi(str);
	return intValue;
}

float *SERIALIZE_Str_Float(char *str)
{
	float *intValue = (float*) malloc(sizeof(float));
	(*intValue) = atoi(str);
	return intValue;
}

TPTable_Row *SERIALIZE_Str_Row(TPDatabase *database,char *str)
{
	if(strcmp(str,"NULL") == 0){
		return NULL;
	}

	/* Split up the str (TABLENAME:ROWID) */
	int amountOfSplits=0;
	char **split = TP_SplitString(str, ':', &amountOfSplits);


	int *tableIdInt = SERIALIZE_Str_Int(split[0]);
	int *col = SERIALIZE_Str_Int(split[1]);

	TPTable_Row *returnRow;
	returnRow = database->Tables[*tableIdInt]->Rows[*col];

	free(tableIdInt);
	free(col);
	free(split[0]);
	free(split[1]);
	free(split);


	return returnRow;
}

char *SERIALIZE_RowID_Path(TPTable *_tbl, int _id)
{
	size_t retSize = snprintf(NULL, 0, "%s/%d.tdf", _tbl->Path, _id) + 1;
	char *ret = (char*)malloc(sizeof(char) * retSize);
	sprintf(ret, "%s/%d.tdf", _tbl->Path, _id);
	return ret;
}
