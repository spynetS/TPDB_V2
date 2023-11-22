#include <stdio.h>
#include <stdlib.h>

#include "../Errors/I_Errors.h"
#include "../Interface/I_Database.h"
#include "../Interface/I_Table.h"

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

int main()
{
	puts("--|UnitTest|--");
	TP_CheckError(TP_TEST_CreateTPDatabase());
	TP_CheckError(TP_TEST_CreateTPTable());
	exit(0);
}
