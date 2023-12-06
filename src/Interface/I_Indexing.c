#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Storage/Storage.h"
#include "../Utils/StringTools.h"
#include "../Utils/MiscTools.h"

enum TP_ERROR_TYPES TP_InsertRowToIndexTable(TPTable *_Table, TPTable_Row *_Row, char *_RangeStr, int _ColIndex)
{
	size_t IndexTablePathSize = snprintf(NULL, 0, "%s%s/%d.cif", _Table->ParentDatabase->ConfigPath, _Table->Name, _ColIndex) + 1;
	char * IndexTablePath = (char*)malloc(sizeof(char) * IndexTablePathSize);
	sprintf(IndexTablePath, "%s%s/%d.cif", _Table->ParentDatabase->ConfigPath, _Table->Name, _ColIndex);

	char *IndexTableStr = strdup("");
	if(access(IndexTablePath, F_OK) == 0)
	{
		free(IndexTableStr);
		IndexTableStr = TP_ReadFile(IndexTablePath);
	}

	int IndexTableLinesCount = 0;
	char **IndexTableLines = NULL;
	int TargetLineInIndex = -1;
	char *Vals = "";
	if(strcmp(IndexTableStr, "") != 0)
	{
		IndexTableLines = TP_SplitString(IndexTableStr, '\n', &IndexTableLinesCount);
		
		if(IndexTableLines == NULL)
		{
			IndexTableLines = (char**)malloc(sizeof(char*));
			IndexTableLines[0] = strdup(IndexTableStr);
			IndexTableLinesCount = 1;
		}

		for (int i = 0; i < IndexTableLinesCount; i++)
		{
			if(strstr(IndexTableLines[i], _RangeStr) != NULL)
			{
				TargetLineInIndex = i;
				int TempKeyValCount = 0;
				char **TempKeyVal = TP_SplitString(IndexTableLines[i], ':', &TempKeyValCount);
				Vals = strdup(TempKeyVal[1]);

				free(TempKeyVal[1]); TempKeyVal[1] = NULL;
				free(TempKeyVal[0]); TempKeyVal[0] = NULL;
				free(TempKeyVal); TempKeyVal = NULL;
				break;
			}
		}
	}

	size_t RowIdSize = snprintf(NULL, 0, "%d", _Row->_ID) + 1;
	char *RowIdStr = (char*)malloc(sizeof(char) * RowIdSize);
	sprintf(RowIdStr, "%d", _Row->_ID);

	char *ValsComplete = "";
	if(TargetLineInIndex == -1)
	{
		ValsComplete = RowIdStr;
	}
	else
	{
		ValsComplete = TP_StrnCat(Vals, 2, ",", RowIdStr);
	}

	char *ToInsert = TP_StrnCat(_RangeStr, 2, ":", ValsComplete);
	if(TargetLineInIndex != -1)
	{
		free(IndexTableLines[TargetLineInIndex]);
		IndexTableLines[TargetLineInIndex] = ToInsert;
	}
	else
	{
		if(IndexTableLines == NULL)
		{
			IndexTableLines = malloc(sizeof(char*) * 1);
		}
		else
		{
			IndexTableLines = realloc(IndexTableLines, sizeof(char*) * (IndexTableLinesCount + 1));
		}
		IndexTableLines[IndexTableLinesCount] = ToInsert;
		IndexTableLinesCount++;
	}

	char *NewIndexTableFile;
	if(IndexTableLinesCount <= 1)
	{
		NewIndexTableFile = strdup(ToInsert);
	}
	else
	{
		NewIndexTableFile = TP_StrnCatArray(IndexTableLines, IndexTableLinesCount, "\n");
	}
	TP_CheckError(TP_StoreFile(IndexTablePath, NewIndexTableFile), TP_EXIT);

	if(IndexTableLines != NULL)
	{
		for (int i = 0; i < IndexTableLinesCount; i++)
		{
			if(IndexTableLines[i] != NULL){ free(IndexTableLines[i]); IndexTableLines[i] = NULL; }
		}
		free(IndexTableLines);
		IndexTableLines = NULL;
	}

	if(ValsComplete != NULL){ free(ValsComplete); ValsComplete = NULL; }
	if(Vals != NULL && strcmp(Vals, "") != 0){ free(Vals); Vals = NULL; }
	
	if(TargetLineInIndex != -1 && RowIdStr != NULL){ free(RowIdStr); RowIdStr = NULL; }
	
	if(NewIndexTableFile != NULL){ free(NewIndexTableFile); NewIndexTableFile = NULL; }

	if(IndexTablePath != NULL){ free(IndexTablePath); IndexTablePath = NULL; }
	if(IndexTableStr != NULL){ free(IndexTableStr); IndexTableStr = NULL; }
	
	return TP_SUCCESS;
}
