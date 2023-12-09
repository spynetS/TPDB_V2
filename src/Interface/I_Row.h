#ifndef I_ROW_H
#define I_ROW_H

#include "../TPDB_Global.h"

TPTable_Row *CreateTPTableRow(int __ID, TPTable *_Table);
void DestroyTPTableRow(TPTable_Row *_self);
void EmptyRowValues(TPTable_Row *_self);

/*
 * Returns the value from the row specified at the column
 * the value is a pointer to the type you want. So if
 * the column is a TP_INT the value will be *int.
 * @param table, the table where the row is from
 * @param row, the row to fetch from
 * @param column, the column in the row to retrive
 * */
void *GetRowValue(TPTable *table,TPTable_Row *row, int column);

/*
 * Returns the values' list but the as void** where the values
 * are the right types
 * (all values are copies of the row value,
 * YOU MUST FREE WITH FreeTypeValues)
 * @param table, the table where the row is from
 * @param row, the row to fetch from
 * */
void** GetTypeValues(TPTable *table, TPTable_Row *row);
/*
 * Frees TypeValues list
 * (all values are copies of the row value, YOU MUST FREE)
 * @param void** tyoevalues, the typelist to free
 * @param size_t arr_size, number of elements in the list
 * EXAMPLE
 *
 * AddRow(MainDatabase->Tables[0], 4, "Ali", "Al Rashini", 19,NULL);
 *
 * TPTable_Row *row = GetRow(MainDatabase->Tables[0], 0);
 * void** values = GetTypeValues(MainDatabase->Tables[0], row);
 *
 * char *firstname = (char*)values[0];
 * char *lastname = (char*)values[1];
 * int age = *(int*) values[2];
 *
 * printf("%s %s is %d years old\n", firstname,lastname,age);
 *
 * FreeTypeValues(values,3);
 * */
void FreeTypeValues(void** typevalues, size_t arr_size);

enum TP_ERROR_TYPES UpdateRow(TPTable *_parent, TPTable_Row *_self);

enum TP_ERROR_TYPES SetRowValues(TPTable *_parent, TPTable_Row *_self, int _count, ...);


#endif
