#include <stdio.h>
#include <stdlib.h>

#include "./Interface/I_Database.h"

TPDatabase *MainDatabase;

void destroy()
{
	DestroyTPDatabase(MainDatabase);
}

int main()
{
	puts("--|MAIN|--");
	MainDatabase = CreateTPDatabase("MainDatabase", "./db");
	destroy();
	exit(0);
}
