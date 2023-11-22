#ifndef I_TABLE_H
#define I_TABLE_H

#include "../TPDB_Global.h"

TPTable *CreateTPTable(char *_Name, char *_Path);
void DestroyTPTable(TPTable *_self);

#endif