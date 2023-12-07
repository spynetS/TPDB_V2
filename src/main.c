#include <stdio.h>
#include <stdlib.h>

#include "./Interface/I_Database.h"
#include "Interface/I_Table.h"
#include "TPDB_Global.h"
#include "./Errors/I_Errors.h"
#include "./Utils/StringTools.h"
#include "./Utils/MiscTools.h"

#include "./Storage/Storage.h"

#include "./Interface/I_Database.h"
#include "./Interface/I_Table.h"
#include "./Interface/I_Row.h"

int main(){
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	AddTable(MainDatabase, "Users");
	SetColumnTypes(MainDatabase->Tables[0], 4, TP_STRING,TP_STRING,TP_INT, TP_FKEY);

	AddRow(MainDatabase->Tables[0], 4, "Ali", "123", 22,NULL);

	TPForeignKey fkey = {"Users", 0};
	AddRow(MainDatabase->Tables[0], 4, "Alfred", "123", 22,&fkey);


	char *str = MainDatabase->Tables[0]->Rows[0]->Values[0];
	puts(str);


	DestroyTPDatabase(MainDatabase);
	return 0;
}
