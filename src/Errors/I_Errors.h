#ifndef I_ERRORS_H
#define I_ERRORS_H

enum TP_ERROR_TYPES
{
	TP_SUCCESS = 0,
	TP_FAILED_CREATETPDATABASE = 101
};

void TP_CheckError(enum TP_ERROR_TYPES err);

#endif