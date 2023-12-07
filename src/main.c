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



void** getTypeValueList(TPTable *table, int _row)
{
	void **values = malloc(sizeof(void*)*table->ColCount);
	TPTable_Row *row = GetRow(table, _row);
	for(int i = 0; i < table->ColCount; i ++){
		/* Create a copy of the value */
		void *gval = GetRowValue(table, row, i);

		values[i] = gval;
	}
	return values;
}
void save_model(char* tablename,void* model, int count, ...) {
	va_list args;
	va_start(args,count);

	for(int i = 0 ; i < count; i++){
		switch(va_arg(args,enum TPTable_Column_Types)){
			case TP_STRING:
				printf("STRING\n");
				break;
			case TP_INT:
				printf("INT\n");
				break;
		}
	}
	va_end(args);
}


void *get_model(void* (*filler)(void **), TPTable *table, int row){
	void **values = getTypeValueList(table,row);
	void *value = filler(values);
	for(int i = 0; i < table->ColCount;i++){
		free(values[i]);
	}
	free(values);
	return value;
}

typedef struct {
	char *firstname;
	char *lastname;
	int age;
} User;


void *new_user(void **values)
{

	User *model = malloc(sizeof(User));
	model->firstname =  strdup((char*) values[0]);
	model->lastname  =  strdup((char*) values[1]);
	model->age       = *(int*)         values[2];

	return model;
}

int main()
{
	TPDatabase *MainDatabase = CreateTPDatabase("MainDatabase", "./db");

	AddTable(MainDatabase, "tables");
	SetColumnTypes(MainDatabase->Tables[0], 3, TP_STRING,TP_STRING,TP_INT);
	TPTable *table = MainDatabase->Tables[0];

	User alfred = {"Alfred", "Roos", 19};
	save_model(NULL,NULL,NULL);

	AddRow(table,3,"ali","al rashini",19);

	User *get = get_model(new_user,table,0);
	puts(get->firstname);
	puts(get->lastname);
	printf("age %d\n",get->age);

	free(get->firstname);
	free(get->lastname);
	free(get);

	DestroyTPDatabase(MainDatabase);
	return 0;
}
