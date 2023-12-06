#ifndef I_ROW_H
#define I_ROW_H

#include "../TPDB_Global.h"

TPTable_Row *CreateTPTableRow(int __ID, TPTable *_Table);
void DestroyTPTableRow(TPTable_Row *_self);

enum TP_ERROR_TYPES UpdateRow(TPTable *_parent, TPTable_Row *_self);

#endif