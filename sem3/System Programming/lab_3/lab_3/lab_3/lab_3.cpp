#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

BOOL GetProcessList();
BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);

int main()
{
	GetProcessList();
	system("pause");
	return 0;
}

BOOL GetProcessList()
{
	HANDLE hProcessSnap; 
	HANDLE hProcess;
	PROCESSENTRY32 pe32; 
	DWORD dwPriorityClass; 

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	pe32.dwSize = sizeof(PROCESSENTRY32); 

	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return(FALSE);
	}

	do
	{
		printf("====================================================");
		_tprintf(TEXT("\nPROCESS NAME:  %s"), pe32.szExeFile);

		dwPriorityClass = 0;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		dwPriorityClass = GetPriorityClass(hProcess);
		CloseHandle(hProcess);

		_tprintf(TEXT("\n  PID          = 0x%08X"), pe32.th32ProcessID);
		_tprintf(TEXT("\n  Parent PID   = 0x%08X"), pe32.th32ParentProcessID);
		_tprintf(TEXT("\n  Priority     = %d"), pe32.pcPriClassBase);
		
		
		if (!ListProcessModules(pe32.th32ProcessID)) {
			printf("\n\n  TOTAL NUMBER OF MODULES = 0");
		};

		_tprintf(TEXT("\n  Thread count          = %d"), pe32.cntThreads);
		ListProcessThreads(pe32.th32ProcessID);

	} while (Process32Next(hProcessSnap, &pe32)); 
	CloseHandle(hProcessSnap);
	return(TRUE);
}

BOOL ListProcessModules(DWORD dwPID)
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32; 

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		return(FALSE);
	}

	me32.dwSize = sizeof(MODULEENTRY32);
	int moduleNumber{ 0 };

	if (!Module32First(hModuleSnap, &me32))
	{
		CloseHandle(hModuleSnap);
		return(FALSE);
	}
	do
	{
		_tprintf(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
		_tprintf(TEXT("\n     Module size = %d"), me32.modBaseSize);
		_tprintf(TEXT("\n     Path        = %s"), me32.szExePath);
		
		++moduleNumber;

	} while (Module32Next(hModuleSnap, &me32));
	CloseHandle(hModuleSnap);

	printf("\n\n  TOTAL NUMBER OF MODULES = %d", moduleNumber);

	return(TRUE);
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	THREADENTRY32 te32;

	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	te32.dwSize = sizeof(THREADENTRY32);

	if (!Thread32First(hThreadSnap, &te32))
	{
		CloseHandle(hThreadSnap);
		return(FALSE);
	}
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			_tprintf(TEXT("\n     Thread priority = %d"), te32.tpBasePri);
			_tprintf(TEXT("\n     THREAD ID       = 0x%08X"), te32.th32ThreadID);
			_tprintf(TEXT("\n"));
		}
	} while (Thread32Next(hThreadSnap, &te32));
	CloseHandle(hThreadSnap);
	return(TRUE);
}