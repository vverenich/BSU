#include <windows.h>
#include <stdio.h>
#include <TlHelp32.h>

#define MAXLENGTH 101

DWORD GetProcessID(char* process) {
	PROCESSENTRY32 processEntry;
	DWORD processID = 0;
	HANDLE Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Snapshot != INVALID_HANDLE_VALUE) {
		processEntry.dwSize = sizeof(processEntry);
		Process32First(Snapshot, &processEntry);

		do {
			if (strcmp(processEntry.szExeFile, process) == 0) {
				processID = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(Snapshot, &processEntry));

		CloseHandle(Snapshot);
	}

	return processID;
}

int fail()
{
	printf("FAIL!\n");
	system("pause");
	return -1;
}

int main(void)
{
	LPCTSTR pipename = "\\\\.\\pipe\\mynamedpipe";					// channel name
	HANDLE hProcessB;												// handle to process B
	LPVOID szAddress;												// address in memory of process B
	DWORD cbWritten, cbRead, dBuf;									// buffers (intermediate)
	BOOL Success;													// flag of successful open / read / write
	DWORD szSize = sizeof(char) * MAXLENGTH;						// the size of the input string
	char* str = (char*)malloc(szSize);								// the string itself
	HANDLE hPipe = INVALID_HANDLE_VALUE;							// channel descriptor
	
	printf("INPUT STRING: ");
	gets_s(str, MAXLENGTH - 1);

	printf("Opening ProcessB...");
	hProcessB = OpenProcess(
		PROCESS_ALL_ACCESS,											// sets the access level to the process object
		FALSE,														// parameter of the inheritance descriptor
		GetProcessID("ProcessB.exe"));								// process ID (in this case, process B)

	if (hProcessB == INVALID_HANDLE_VALUE) return fail();

	printf("\nAllocating memory for ProcessB...");
	szAddress = VirtualAllocEx(

		hProcessB,													// process handle (in this case, process B)
		0,															// the system itself decides where to allocate memory
		szSize,														// amount of reserved memory
		MEM_RESERVE |												// memory is reserved and freed
		MEM_COMMIT,
		PAGE_EXECUTE_READWRITE);									// protection attribute
	
	printf("\nWriting your string in ProcessB memory...");
	Success = WriteProcessMemory(
		hProcessB,											        // process handle (in this case, process B)
		szAddress,													// where to write
		str,														// what to write
		szSize,														// amount of data to be written
		0);															// pointer to a variable that receives the number of bytes passed to the specified process (ignored)
	if (Success == FALSE) return fail();

	printf("\nConnecting to named pipe...");
	while (hPipe == INVALID_HANDLE_VALUE) {
		hPipe = CreateFile(
			pipename,												// named pipe name
			GENERIC_READ |											// require read and write access
			GENERIC_WRITE,
			0,														// no sharing
			NULL,													// no security descriptors
			OPEN_EXISTING,											// open an existing channel
			0,														// default file attributes
			NULL);													// no template file descriptor
	}

	printf("\ nWriting memory address ...");
	dBuf = (DWORD)szAddress;
	Success = WriteFile(
		hPipe,														// pipe handle
		&dBuf,														// data to write (in this case - memory address in process B)
		sizeof(dBuf),												// amount of recorded data
		&cbWritten,													// amount of data written (not used)
		NULL);														// asynchronous buffer (not used)
	if (Success == FALSE) return fail();
	printf("\ nWaiting answer from ProcessB ...");
	Success = ReadFile(
		hPipe,														// named pipe name
		&szAddress,													// read buffer
		sizeof(szAddress),											// amount of data read
		&cbRead,													// amount of data read (do not use)
		NULL);														// asynchronous buffer (not used)
	if (Success == FALSE) return fail();

	printf("\nReleasing ProcessB memory...");
	Success = VirtualFreeEx(
		hProcessB,
		szAddress,
		0,
		MEM_RELEASE);
	if (Success == FALSE) return fail();

	printf("\nClosing named pipe...");
	Success = CloseHandle(hPipe);
	if (Success == FALSE) return fail();

	printf("\nClosing ProcessB...");
	Success = CloseHandle(hProcessB);
	if (Success == FALSE) return fail();

	printf("\nProcessA was finished...\n");
	system("pause");
	return 0;
}
