#include <windows.h>
#include <conio.h>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {
    
    int arraySize = atoi(argv[1]);
    HANDLE hWritePipe = (HANDLE)atoi(argv[2]);
    HANDLE ﻿hReadPipe = (HANDLE)atoi(argv[3]);
    std::vector<float> vec;

    HANDLE hEnableRead = OpenEventA(EVENT_ALL_ACCESS, FALSE, "EnableRead");

    for (int i = 0; i < arraySize; i++) {
        float nData;
        DWORD dwBytesRead;
        if (!ReadFile(﻿hReadPipe, &nData, sizeof(nData), &dwBytesRead, NULL)) {
            _cputs("Read from the pipe failed.\n");
            std::cout << (GetLastError()) << "\n";
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %.3f is read from the pipe.\n", nData);
        vec.push_back(nData);
    }
    _cputs("The process finished reading from the pipe.\n");
    


    _cputs("Press any key to continue communication.\n");
    _getch();
    SetEvent(hEnableRead);

    float result = 1.0;
    for (float x : vec) {
        result *= x;
    }

    DWORD dwBytesWritten;
    if (!WriteFile(hWritePipe, &result, sizeof(result), &dwBytesWritten, NULL)) {
        _cputs("Write to file failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    _cprintf("Result: %.3f is written to the pipe.\n", result);

    CloseHandle(﻿hReadPipe);
    CloseHandle(hWritePipe);
    CloseHandle(hEnableRead);

    _cputs("The process finished writing to the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return 0;

}