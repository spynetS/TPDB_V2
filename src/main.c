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

#include <stdarg.h>

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


void save_model(void* model, enum TPTable_Column_Types first, ...) {
    va_list args;
    enum TPTable_Column_Types value;

    va_start(args, first);

    // Process variable arguments until a sentinel value is encountered
    while ((value = va_arg(args, enum TPTable_Column_Types)) != -1) {
        printf("Next Argument: %d\n", value);
    }

    va_end(args);
}

typedef struct {
	TPTable *mytable;
	void *model;

} ModelHolder;

typedef struct {
	char *name;
	int age;
} User;

int main()
{
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	User alfred = {"Alfred", 180};
	save_model(&alfred, TP_STRING, TP_INT);

	DestroyTPDatabase(MainDatabase);
	return 0;
}
