#ifndef I_TABLE_H
#define I_TABLE_H

#include "../TPDB_Global.h"
#include "I_Database.h"

TPTable *CreateTPTable(char *_Name, TPDatabase *_Database, int _lazyLoadRows);
void DestroyTPTable(TPTable *_self);

enum TP_ERROR_TYPES SetColumnTypes(TPTable *_self, int _count, ...);
enum TP_ERROR_TYPES AddRow(TPTable *_self, int _count, ...);

#endif