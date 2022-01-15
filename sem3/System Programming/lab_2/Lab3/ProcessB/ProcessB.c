#include <windows.h>
#include <stdio.h>

int fail()
{
	printf("FAIL!\n");
	system("pause");
	return -1;
}

int main(void) {
	LPCTSTR pipename = "\\\\.\\pipe\\mynamedpipe";					// channel name
	HANDLE hNamedPipe;												// handle to named pipe
	DWORD szAddress;												// address of allocated memory
	DWORD cbRead, cbWritten;										// buffers (intermediate)
	char* msg;														// the resulting string
	BOOL Success;													// flag of successful open / read / write

	printf("Creating pipe...");
	hNamedPipe = CreateNamedPipe(
		pipename,													// channel name
		PIPE_ACCESS_DUPLEX,											// bidirectional channel; server and client processes can read from and write to the pipe
		PIPE_TYPE_MESSAGE |											// data is written to and read from the pipe as a stream of messages
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,													// unlimited waiting while executing actions by the client process
		PIPE_UNLIMITED_INSTANCES,									// maximum number of instances
		sizeof(DWORD),												// reserve for the output buffer
		sizeof(DWORD),												// reserve for the input buffer
		100,														// default time-out value specifier (not used)
		NULL);														// security attributes
	if (hNamedPipe == INVALID_HANDLE_VALUE) return fail();

	printf("\nConnecting to pipe...");
	ConnectNamedPipe(hNamedPipe, NULL);

	printf("\nReading from pipe...");
	Success = ReadFile(
		hNamedPipe,													// named pipe name
		&szAddress,													// read buffer
		sizeof(szAddress),											// amount of data read
		&cbRead,													// amount of data read (do not use)
		NULL);														// asynchronous buffer (not used)
	if (Success == FALSE) return fail();

	printf("\nYour string: ");
	msg = (char*)szAddress;
	printf_s("%s\n", msg);

	printf("Sending answer to ProccessA...");
	Success = WriteFile(
		hNamedPipe,													// pipe handle
		&szAddress,													// data to write
		sizeof(szAddress),											// amount of data to be written
		&cbWritten,													// amount of data written (not used)
		NULL);														// asynchronous buffer (not used)
	if (Success == FALSE) return fail();

	printf("\nDisconnecting from named pipe...");
	Success = DisconnectNamedPipe(hNamedPipe);
	if (Success == FALSE) return fail();

	printf("\nClosing named pipe...");
	Success = CloseHandle(hNamedPipe);
	if (Success == FALSE) return fail();

	printf("\nProcessB was finished...\n");
	system("pause");
	return 0;
}