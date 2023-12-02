#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "StringTools.h"

char *TP_StrnCat(char *_baseString, int _count, ...)
{
	va_list args;
	va_start(args, _count);
	char *retStr = _baseString;

	for (size_t i = 0; i < _count; i++)
	{
		char *tempStr = va_arg(args, char*);
		int _strSize = snprintf(NULL, 0, "%s%s", retStr, tempStr) + 1;
		char *_str = (char *)malloc(sizeof(char) * _strSize);
		sprintf(_str, "%s%s", retStr, tempStr);

		if (retStr != _baseString && retStr != NULL)
		{
			free(retStr);
		}

		retStr = _str;
	}

	va_end(args);
	return retStr;
}

/*
	@brief Joins array of strings
	@exception {ERROR_CODE: 502}
	@attention Make sure to free the _list after this function.
	@attention TP_StrnCatArray does not free anything you pass.

	@param _list		String array
	@param _count		Count of strings in array
	@param _separator	What to seperate the strings with.

	@return {char*} The concatinated string of _list
*/
char *TP_StrnCatArray(char **_list, int _count, char *_separator)
{
	char *retStr = strdup(_list[0]);

	for (size_t i = 1; i < _count; i++)
	{
		char *tempStr = strdup(_list[i]);
		int _strSize = snprintf(NULL, 0, "%s%s%s", retStr, _separator, tempStr) + 1;
		char *_str = (char *)malloc(sizeof(char) * _strSize);
		sprintf(_str, "%s%s%s", retStr, _separator, tempStr);

		if (retStr != "" && retStr != NULL)
		{
			free(retStr);
		}

		retStr = _str;
		free(tempStr);
	}

	return retStr;
}
