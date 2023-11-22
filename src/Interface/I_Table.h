#ifndef I_TABLE_H
#define I_TABLE_H

#include "../TPDB_Global.h"
#include "I_Database.h"

TPTable *CreateTPTable(char *_Name, TPDatabase *_Database);
void DestroyTPTable(TPTable *_self);

#endif