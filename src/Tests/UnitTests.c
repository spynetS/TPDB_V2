#include <stdio.h>
#include <stdlib.h>

#include "../Errors/I_Errors.h"
#include "../Interface/I_Database.h"

enum TP_ERROR_TYPES TP_TEST_CreateTPDatabase()
{
	puts("--|TP_TEST_CreateTPDatabase|--");
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	if(MainDatabase != NULL)
	{
		DestroyTPDatabase(MainDatabase);
		return TP_SUCCESS;
	}
	else
	{
		DestroyTPDatabase(MainDatabase);
		return TP_FAILED_CREATETPDATABASE;
	}
}

int main()
{
	puts("--|UnitTest|--");

	TP_CheckError(TP_TEST_CreateTPDatabase());
	exit(0);
}
