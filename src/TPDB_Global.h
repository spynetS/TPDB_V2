#ifndef TPDB_GLOBAL_H
#define TPDB_GLOBAL_H

enum TPTable_Column_Types
{
	TP_INT,
	TP_FLOAT,
	TP_STRING,
	TP_CHAR,
	TP_FKEY
};

typedef struct
{
	int _ID;
	int ValCount;
	char **Values;
} TPTable_Row;

typedef struct
{
	int _ID;
	char *Name;
	char *Path;

	int ColCount;
	int RowCount;

	enum TPTable_Column_Types *ColumnTypes;
	TPTable_Row **Rows;
} TPTable;

typedef struct
{
	int _ID;
	char *Name;
	char *Path;
	TPTable *Tables;
} TPDatabase;

#endif