#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Errors/I_Errors.h"
#include "../Utils/StringTools.h"
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
	TPTable *NewTable = CreateTPTable("/TestTable", MainDatabase);
	
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
	TPTable *NewTable = CreateTPTable("/TestTable", MainDatabase);
	NewTable->ColCount = 2;
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

int main()
{
	puts("--|UnitTest|--");
	TP_CheckError(TP_TEST_STRNCAT());

	TP_CheckError(TP_TEST_CreateTPDatabase());
	TP_CheckError(TP_TEST_CreateTPTable());
	TP_CheckError(TP_TEST_CreateTPTableRow());
	exit(0);
}
