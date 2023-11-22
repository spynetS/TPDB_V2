#ifndef I_ROW_H
#define I_ROW_H

#include "../TPDB_Global.h"

TPTable_Row *CreateTPTableRow(int __ID, TPTable *_Table);
void DestroyTPTableRow(TPTable_Row *_self);

#endif