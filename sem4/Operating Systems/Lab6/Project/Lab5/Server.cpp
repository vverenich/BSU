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

    char c;// служебный символ
    SECURITY_ATTRIBUTES sa;// атрибутызащиты
    SECURITY_DESCRIPTOR sd;// дескрипторзащиты
    HANDLE hNamedPipe;
    char lpszInMessage[80];// для сообщения от клиента
    DWORD dwBytesRead;// для числа прочитанных байтов
    char lpszOutMessage[] = "The server has received a message.";// обратноесообщение
    DWORD dwBytesWrite;// для числа записанных байтов
                       // инициализация атрибутов защиты
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = FALSE;// дескриптор канала ненаследуемый
                              // инициализируемдескрипторзащиты
    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);// устанавливаем атрибуты защиты, разрешая доступ всем пользователям
    SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
    sa.lpSecurityDescriptor = &sd;// создаем именованный канал для чтения
    hNamedPipe = CreateNamedPipe(
        L"\\\\.\\pipe\\demo_pipe", // имяканала
        PIPE_ACCESS_DUPLEX,// читаем из канала и пишем в канал
        PIPE_TYPE_MESSAGE | PIPE_WAIT,// синхронная передача сообщений
        1,// максимальное количество экземпляров канала 
        0,// размер выходного буфера по умолчанию
        0,// размер входного буфера по умолчанию
        INFINITE,// клиент ждет связь 500 мс
        &sa// доступ для всех пользователей
    );// проверяем на успешное создание

    if (hNamedPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Creation of the named pipe failed." << std::endl << "The last error code: " << GetLastError() << std::endl;
        std::cout << "Press any char to finish server: ";
        std::cin >> c;
        return 0;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    std::wstring commandLine = L"Mult.exe " + std::to_wstring(arraySize);
    if (!CreateProcess(NULL, const_cast<wchar_t*>(commandLine.c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si,  &pi)) {
        _cputs("Create process failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }

    std::cout << "The server is waiting for connection with a client." << std::endl;
    if (!ConnectNamedPipe(
        hNamedPipe, // дескрипторканала
        (LPOVERLAPPED)NULL// связьсинхронная
    )) {
        std::cerr << "The connection failed." << std::endl << "The last error code: " << GetLastError() << std::endl;
        CloseHandle(hNamedPipe);
        std::cout << "Press any char to finish the server: ";
        std::cin >> c;
        return 0;
    }


    std::cout << "\n";
    for (float x : vec) {
        if (!WriteFile(hNamedPipe,// дескриптор канала
            &x,// адрес буфера для вывода данных
            sizeof(x),// число записываемых байтов
            &dwBytesWrite,// число записанных байтов
            (LPOVERLAPPED)NULL// передача данных синхронная
        )) {
            _cputs("Write to file failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %.3f is written to the pipe.\n", x);
    }
    _cputs("The process finished writing to the pipe.\n");


    float nData;
    if (!ReadFile(hNamedPipe,// дескрипторканала
        &nData,// адрес буфера для ввода данных
        sizeof(nData),// число читаемых байтов
        &dwBytesRead,// число прочитанных байтов
        (LPOVERLAPPED)NULL// передача данных синхронная
    )) {

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

	printArray(vec);
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