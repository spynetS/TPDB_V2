#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Utils/StringTools.h"
#include "../Utils/MiscTools.h"

#include "../Storage/Storage.h"

#include "../Interface/I_Database.h"
#include "../Interface/I_Table.h"
#include "../Interface/I_Row.h"

enum TP_ERROR_TYPES TP_TEST_STRNCAT()
{
	printf("--|TP_TEST_STRNCAT|--: ...");
	char *test_1 = TP_StrnCat("", 2, "hello ", "world!");
	char *test_2 = TP_StrnCat("How ", 2, "are ", "you?");

	if(strcmp(test_1, "hello world!") == 0 && strcmp(test_2, "How are you?") == 0)
	{
		free(test_1);
		free(test_2);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		free(test_1);
		free(test_2);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_STRNCAT;
	}
}

enum TP_ERROR_TYPES TP_TEST_STRNCATARRAY()
{
	printf("--|TP_TEST_STRNCATARRAY|--: ...");
	char **tempArray = (char**)malloc(sizeof(char*) * 2);
	tempArray[0] = strdup("hello");
	tempArray[1] = strdup("world!");

	char *res = TP_StrnCatArray(tempArray, 2, " ");
	puts(res);

	if(res != NULL && strcmp(res, "hello world!") == 0)
	{
		free(tempArray[1]);
		free(tempArray[0]);
		free(tempArray);
		free(res);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		free(tempArray[1]);
		free(tempArray[0]);
		free(tempArray);
		free(res);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_STRNCATARRAY;
	}
}

enum TP_ERROR_TYPES TP_TEST_SPLITSTRING()
{
	printf("--|TP_TEST_SPLITSTRING|--: ...");
	char *tempStr = "hello,how,are,you, bro";

	int splitCount = 0;
	char **splitStr = TP_SplitString(tempStr, ',', &splitCount);

	if(strcmp(splitStr[0], "hello") == 0 && strcmp(splitStr[1], "how") == 0 && 
	strcmp(splitStr[2], "are") == 0 && strcmp(splitStr[3], "you") == 0
	)
	{
		for (int i = 0; i < splitCount; i++)
		{
			if(splitStr[i] != NULL){free(splitStr[i]); splitStr[i] = NULL;}
		}
		if(splitStr != NULL) { free(splitStr); }
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		for (int i = 0; i < splitCount; i++)
		{
			if(splitStr[i] != NULL){free(splitStr[i]); splitStr[i] = NULL;}
		}
		if(splitStr != NULL) { free(splitStr); }
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_SPLITSTRING;
	}
}

enum TP_ERROR_TYPES TP_TEST_AppendToArrayOfPointers()
{
	printf("--|TP_TEST_AppendToArrayOfPointers|--: ...");
	char **TestStrArray = NULL;
	size_t TestStrArrayLen = 0;

	char *str1 = "Hello";
	char *str2 = "World";
	TP_CheckError(AppendToArrayOfPointers((void***)&TestStrArray, &TestStrArrayLen, str1, sizeof(char*)), TP_EXIT);
	TP_CheckError(AppendToArrayOfPointers((void***)&TestStrArray, &TestStrArrayLen, str2, sizeof(char*)), TP_EXIT);

	if(strcmp(TestStrArray[0], "Hello") == 0 && strcmp(TestStrArray[1], "World") == 0 && TestStrArrayLen == 2)
	{
		if(TestStrArray[0] != NULL){ free(TestStrArray[0]); }
		if(TestStrArray[1] != NULL){ free(TestStrArray[1]); }
		if(TestStrArray != NULL){ free(TestStrArray); TestStrArray = NULL; }

		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		if(TestStrArray[0] != NULL){ free(TestStrArray[0]); }
		if(TestStrArray[1] != NULL){ free(TestStrArray[1]); }
		if(TestStrArray != NULL){ free(TestStrArray); TestStrArray = NULL; }

		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_AppendToArrayOfPointers;
	}
}

enum TP_ERROR_TYPES TP_TEST_FreeArrayOfPointers()
{
	printf("--|TP_TEST_FreeArrayOfPointers|--: ...");
	char **TestStrArray = NULL;
	size_t TestStrArrayLen = 0;

	char *str1 = "Hello";
	char *str2 = "World";
	TP_CheckError(AppendToArrayOfPointers((void***)&TestStrArray, &TestStrArrayLen, str1, sizeof(char*)), TP_EXIT);
	TP_CheckError(AppendToArrayOfPointers((void***)&TestStrArray, &TestStrArrayLen, str2, sizeof(char*)), TP_EXIT);

	TP_CheckError(FreeArrayOfPointers((void***)&TestStrArray, TestStrArrayLen), TP_EXIT);

	if(TestStrArray == NULL)
	{
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_FreeArrayOfPointers;
	}
}

enum TP_ERROR_TYPES TP_TEST_CreateTPDatabase()
{
	printf("--|TP_TEST_CreateTPDatabase|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	if(MainDatabase != NULL)
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_CREATETPDATABASE;
	}
}

enum TP_ERROR_TYPES TP_TEST_CreateTPTable()
{
	printf("--|TP_TEST_CreateTPTable|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	TPTable *NewTable = CreateTPTable("/TestTable", MainDatabase, TP_FALSE);
	
	if(NewTable != NULL)
	{
		DestroyTPTable(NewTable);
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPTable(NewTable);
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_CREATETPTABLE;
	}
}

enum TP_ERROR_TYPES TP_TEST_CreateTPTableRow()
{
	printf("--|TP_TEST_CreateTPTableRow|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	TPTable *NewTable = CreateTPTable("/TestTable", MainDatabase, TP_FALSE);
	NewTable->ColCount = 2;
	SetColumnTypes(NewTable, 2, TP_STRING, TP_STRING);
	TPTable_Row *NewRow = CreateTPTableRow(0, NewTable);

	if(NewRow != NULL)
	{
		DestroyTPTableRow(NewRow);
		DestroyTPTable(NewTable);
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPTableRow(NewRow);
		DestroyTPTable(NewTable);
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_CREATETPTABLEROW;
	}
}

enum TP_ERROR_TYPES TP_TEST_AddTable()
{
	printf("--|TP_TEST_AddTable|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	AddTable(MainDatabase, "Users");

	if(MainDatabase != NULL)
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_AddTable;
	}
}

enum TP_ERROR_TYPES TP_TEST_AddRow()
{
	printf("--|TP_TEST_AddRow|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	
	AddTable(MainDatabase, "Users");
	SetColumnTypes(MainDatabase->Tables[0], 3, TP_STRING, TP_STRING, TP_INT);
	AddRow(MainDatabase->Tables[0], 3, "Ali", "123", 22);

	if(MainDatabase != NULL)
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_AddTable;
	}
}

enum TP_ERROR_TYPES TP_TEST_InsertRowToIndexTable()
{
	printf("--|TP_TEST_InsertRowToIndexTable|--: ...");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	
	AddTable(MainDatabase, "Users");
	MainDatabase->Tables[0]->ColumnsIndexOffset = 10;
	SetColumnTypes(MainDatabase->Tables[0], 3, TP_STRING, TP_STRING, TP_INT);
	AddIndexColumn(MainDatabase->Tables[0], 2);

	AddRow(MainDatabase->Tables[0], 3, "Ali", "123", 22);
	AddRow(MainDatabase->Tables[0], 3, "Alfred", "asd", 2);
	AddRow(MainDatabase->Tables[0], 3, "ludde", "ass", 23);
	AddRow(MainDatabase->Tables[0], 3, "lukass", "ad", 60);

	if(MainDatabase != NULL)
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_SUCCESS);
		printf("\n");
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPDatabase(MainDatabase);
		printf(ERROR_ASCII_FAIL);
		printf("\n");
		return TP_FAILED_AddTable;
	}
}

int main()
{
	puts("--|UnitTest|--");
	TP_CheckError(TP_TEST_STRNCAT(), TP_EXIT);
	TP_CheckError(TP_TEST_STRNCATARRAY(), TP_EXIT);
	TP_CheckError(TP_TEST_SPLITSTRING(), TP_EXIT);

	TP_CheckError(TP_TEST_AppendToArrayOfPointers(), TP_EXIT);
	TP_CheckError(TP_TEST_FreeArrayOfPointers(), TP_EXIT);

	TP_CheckError(TP_Mkdir("./db"), TP_IGNORE);
	TP_CheckError(TP_StoreFile("./db/test.txt", "TechP"), TP_EXIT);
	char *tempReadFile = TP_ReadFile("./db/test.txt");
	if(strcmp(tempReadFile, "TechP") != 0){ free(tempReadFile); TP_CheckError(TP_FAILED_READFILE, TP_EXIT); }
	free(tempReadFile);

	TP_CheckError(TP_TEST_CreateTPDatabase(), TP_EXIT);
	TP_CheckError(TP_TEST_CreateTPTable(), TP_EXIT);
	TP_CheckError(TP_TEST_CreateTPTableRow(), TP_EXIT);

	TP_CheckError(TP_TEST_AddTable(), TP_EXIT);
	TP_CheckError(TP_TEST_AddRow(), TP_EXIT);
	TP_CheckError(TP_TEST_InsertRowToIndexTable(), TP_EXIT);
	exit(0);
}
