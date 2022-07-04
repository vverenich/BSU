#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <random>
#include <string>
#include <ctime>

std::vector<float> generateArray(int size);

void printArray(const std::vector<float>& arr);

int main() {
	int arraySize{};
	std::cout << "Enter array size: ";
	std::cin >> arraySize;
	std::vector<float> vec = generateArray(arraySize);
	printArray(vec);

    HANDLE hWritePipe, hReadPipe;
    HANDLE hEnableRead = CreateEventA(NULL, FALSE, FALSE, "EnableRead");
    HANDLE hEnableReadFromServer = CreateEventA(NULL, FALSE, FALSE, "reader");

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa;// создаем событие для синхронизации обмена данными
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;// защитапоумолчанию
    sa.bInheritHandle = TRUE;// дескрипторынаследуемые
    
    // создаем анонимный канал
    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        std::cout << "Create pipe failed.\n";
        _getch();
        return GetLastError();
    }

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    std::wstring commandLine = L"Mult.exe " + std::to_wstring(arraySize) + L" " + std::to_wstring((int)hWritePipe) + L" " + std::to_wstring((int)hReadPipe);
    if (!CreateProcess(NULL, const_cast<wchar_t*>(commandLine.c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si,  &pi)) {
        _cputs("Create process failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    std::cout << "\n";
    for (float x : vec) {
        DWORD dwBytesWritten;
        if (!WriteFile(hWritePipe, &x, sizeof(x), &dwBytesWritten, NULL)) {
            _cputs("Write to file failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %.3f is written to the pipe.\n", x);
    }
    _cputs("The process finished writing to the pipe.\n");

    WaitForSingleObject(hEnableRead, INFINITE);

    float nData;
    DWORD dwBytesRead;
    if (!ReadFile(hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL)) {

        _cputs("Read from the pipe failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    std::cout << "\n" << "Result of Mult.exe: " << nData << "\n";
    std::cout << "Sent array: ";
    printArray(vec);

    _cputs("\nThe process finished reading from the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
    CloseHandle(hEnableRead);

	//printArray(vec);
}


std::vector<float> generateArray(int size) {
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> urd(-10, 10);
    std::vector<float> arr(size);
    for (auto& x : arr) {
        x = urd(gen);
    }

    return arr;
}

void printArray(const std::vector<float>& arr) {
    std::cout << "[ ";
    for (const auto& x : arr) {
        std::cout << x << " ";
    }
    std::cout << "]";
}