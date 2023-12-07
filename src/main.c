#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./Errors/I_Errors.h"
#include "./Utils/StringTools.h"
#include "./Utils/SerializeTools.h"
#include "./Utils/MiscTools.h"

#include "./Storage/Storage.h"

#include "./Interface/I_Database.h"
#include "Interface/I_Table.h"
#include "./Interface/I_Row.h"
#include "TPDB_Global.h"

int Main_Ali_Test()
{
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	
	AddTable(MainDatabase, "Users");
	TPTable *UsersTable = MainDatabase->Tables[0];
	UsersTable->RowsOnDemand = TP_TRUE;

	SetColumnTypes(UsersTable, 3, TP_STRING, TP_STRING, TP_INT);
	AddRow(UsersTable, 3, "Ali", "123", 22);

	// Get Row lazyLoad enabled.
	TPTable_Row *Row = GetRow(UsersTable, 0);

	int *age = (int*)GetRowValue(UsersTable, Row, 2); //Update age value
	(*age) = 50;

	SetRowValues(UsersTable, Row, UsersTable->ColCount, "hi", TP_KEEP_ROW_VAL_PTR, (*age));
	UpdateRow(UsersTable, Row);
	
	free(age); age = NULL;
	DestroyTPDatabase(MainDatabase);
	return 0;
}

int main()
{
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	AddTable(MainDatabase, "Users");
	TPTable *usersTable = MainDatabase->Tables[0];
	SetColumnTypes(MainDatabase->Tables[0], 4, TP_STRING,TP_STRING,TP_INT, TP_FKEY);

	AddRow(MainDatabase->Tables[0], 4, "Ali", "123", 22,NULL);

	TPForeignKey fkey = {0, 0};
	AddRow(MainDatabase->Tables[0], 4, "Alfred", "123", 22, &fkey);


	TPTable_Row *me = GetRow(usersTable,1);

	TPTable_Row *friend = GetRowValue(usersTable,me,3);
	if(friend != NULL)
		puts(friend->Values[0]);
	char* name = GetRowValue(usersTable,me,0);
	puts(name);
	free(name);


	DestroyTPDatabase(MainDatabase);
	return 0;
}
