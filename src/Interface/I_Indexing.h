#ifndef I_INDEXING_H
#define I_INDEXING_H

#include "../TPDB_Global.h"

enum TP_ERROR_TYPES TP_InsertRowToIndexTable(TPTable *_Table, TPTable_Row *_Row, char *_RangeStr, int _ColIndex);

#endif