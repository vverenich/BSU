#include <iostream>
#include <windows.h>

int main(int args, char* argv[])
{
    HANDLE mutex;
    HANDLE events[2];
    HANDLE signal_event_from_writer;

    mutex = OpenMutex(SYNCHRONIZE, FALSE, L"writer_mutex");
    if (mutex == NULL) // завершение процесса при неуачи открытия мьютекса
    {
        std::cerr << "Can't open mutex\n";
        system("pause");
        return GetLastError();
    }

    if (args != 2)
    {
        std::cerr << "Wrong parameters amount\n";
        system("pause");
        CloseHandle(mutex);
        return GetLastError();
    }
    int n = atoi(argv[1]);

    if (n <= 0)
    {
        std::cerr << "Wrong messages amount\n";
        CloseHandle(mutex);
        system("pause");
        return GetLastError();
    }

    events[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"A_writer");
    events[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"B_writer");

    signal_event_from_writer = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"signal_from_writer");

    for (size_t i = 0; i < 2; ++i) // завершение проесса при неудаче открытия одного из событий
        if (events[i] == NULL)
        {
            for (size_t j = 0; j < 2; ++j)
                if (events[j] != NULL)
                    CloseHandle(events[i]);
            std::cerr << "Can't open event\n";
            system("pause");
            CloseHandle(mutex);
            return GetLastError();
        }

    for (size_t i = 0; i < n; ++i)
    {
        WaitForSingleObject(mutex, INFINITE); //ожидание входа
        std::cout << "activ";

        char res;
        std::cout << "Choose the message type: \n" // получение сообщения от пользователя
            "A\n"
            "B\n"
            "input: ";

        std::cin >> res;
        switch (res)  // отправка сообщения Administrator
        {
        case 'A':
            PulseEvent(events[0]);
            break;
        case 'B':
            PulseEvent(events[1]);
            break;
        default:
            std::cerr << "Wrong data\n";
            --i;
        }
        ReleaseMutex(mutex); // выход из мьютекса
        std::cout << "realise";
    }

    std::cout << "I'm done!\n";
    //system("pause");
    for (size_t i = 0; i < 2; ++i)
        CloseHandle(events[i]);
    CloseHandle(mutex);
    SetEvent(signal_event_from_writer);
    return 0;
}

