#ifndef I_DATABASE_H
#define I_DATABASE_H

#include "../TPDB_Global.h"

TPDatabase *CreateTPDatabase(char *_Name, char *_Path);
void DestroyTPDatabase(TPDatabase *_self);

enum TP_ERROR_TYPES AddTable(TPDatabase *_self, char *_Name);
enum TP_ERROR_TYPES GetTable(TPDatabase *_self, char *_Name);

#endif