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
	int result = _snprintf_s(buffer, dwBufferSize, 60, "Displays the contents of the current working directory");
	*pdwBytesWritten = result;
	return result;
}

VOID Execute() 
{
	system("dir");
	printf("\n");
}