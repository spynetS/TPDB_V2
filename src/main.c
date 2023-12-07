#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./Errors/I_Errors.h"
#include "./Utils/StringTools.h"
#include "./Utils/MiscTools.h"

#include "./Storage/Storage.h"

#include "./Interface/I_Database.h"
#include "./Interface/I_Table.h"
#include "./Interface/I_Row.h"

#include "TPDB_Global.h"

int main()
{
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	AddTable(MainDatabase, "Users");
	SetColumnTypes(MainDatabase->Tables[0], 3, TP_STRING,TP_STRING,TP_INT);
	AddRow(MainDatabase->Tables[0], 3, "Ali", "123", 22);

	DestroyTPDatabase(MainDatabase);
	exit(0);
}
