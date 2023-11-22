#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "StringTools.h"

char *TP_StrnCat(char *_baseString, int _count, ...) {
	va_list args;
	va_start(args, _count);
	char *retStr = _baseString;

	for (size_t i = 0; i < _count; i++) {
		char *tempStr = va_arg(args, char*);
		int _strSize = snprintf(NULL, 0, "%s%s", retStr, tempStr) + 1;
		char *_str = (char *)malloc(sizeof(char) * _strSize);
		sprintf(_str, "%s%s", retStr, tempStr);

		if (retStr != _baseString && retStr != NULL) {
			free(retStr);
		}

		retStr = _str;
	}

	va_end(args);
	return retStr;
}
