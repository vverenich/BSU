#include <windows.h>
#include <conio.h>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {
    
    int arraySize = atoi(argv[1]);
    std::vector<float> vec;

    char c;// служебный символ
    HANDLE hNamedPipe;
    DWORD dwBytesWritten;// для числа записанных байтов
    DWORD dwBytesRead;// для числа прочитанных байтов

    hNamedPipe = CreateFile(
        L"\\\\.\\pipe\\demo_pipe",// имяканала
        GENERIC_READ | GENERIC_WRITE,// читаем и записываем в канал
        FILE_SHARE_READ | FILE_SHARE_WRITE,// разрешаем чтение и запись в канал
        (LPSECURITY_ATTRIBUTES)NULL,// защитапоумолчанию
        OPEN_EXISTING,// открываем существующий канал
        FILE_ATTRIBUTE_NORMAL,// атрибутыпоумолчанию
        (HANDLE)NULL// дополнительных атрибутов нет
    );// проверяем связь с каналом

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Connection with the named pipe failed." << std::endl << "The last error code: " << GetLastError() << std::endl;
        std::cout << "Press any char to finish the client: ";
        std::cin >> c;
        return 0;
    }

    for (int i = 0; i < arraySize; i++) {
        float nData;
        if (!ReadFile(
            hNamedPipe,
            &nData,
            sizeof(nData),
            &dwBytesRead,
            (LPOVERLAPPED)NULL
        )) {
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

    float result = 1.0;
    for (float x : vec) {
        result *= x;
    }


    if (!WriteFile(
        hNamedPipe,// дескрипторканала
        &result,// данные
        sizeof(result),// размерданных
        &dwBytesWritten,// количество записанных байтов
        (LPOVERLAPPED)NULL// синхронная запись
    )) {
        _cputs("Write to file failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    _cprintf("Result: %.3f is written to the pipe.\n", result);

    _cputs("The process finished writing to the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();
    return 0;

}