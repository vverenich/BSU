#include "dll.h"
#include <stdio.h>

BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD *pdwBytesWritten)
{
	int result = _snprintf_s(buffer, dwBufferSize, 20, "Vladislav Verenich");
	*pdwBytesWritten = result;
	return result;
}

BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD *pdwBytesWritten)
{
	int result = _snprintf_s(buffer, dwBufferSize, 50, "Changes the color of console to green");
	*pdwBytesWritten = result;
	return result;
}

VOID Execute()
{
	system("color a");
	printf("\n");
}