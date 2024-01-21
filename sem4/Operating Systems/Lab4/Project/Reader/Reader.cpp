#include <iostream>
#include <windows.h>

int main(int args, char* argv[])
{
	HANDLE semaphore;
	HANDLE events[2];
	HANDLE signal_event_from_reader;
	char msgs[] = { 'A', 'B' };

	if (args != 2)
	{
		std::cerr << "Wrong parameters amount\n";
		system("pause");
		return GetLastError();
	}
	int n = atoi(argv[1]);

	if (n <= 0)
	{
		std::cerr << "Wrong messages amount\n";
		system("pause");
		return GetLastError();
	}

	semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"reader_semaphore");

	if (semaphore == NULL) // завершение процесса при неудаче в открытии семафора
	{
		std::cerr << "Can't open semaphore\n";
		system("pause");
		return GetLastError();
	}

	events[0] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"A_writer");
	events[1] = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"B_writer");

	signal_event_from_reader = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"signal_from_reader");

	for (size_t i = 0; i < 2; ++i) // завершение процесса при неудачи в открытии одного из событий
		if (events[i] == NULL)
		{
			for (size_t j = 0; j < 2; ++j)
				if (events[j] != NULL)
					CloseHandle(events[i]);
			std::cerr << "Can't open event\n";
			system("pause");
			CloseHandle(semaphore);
			return GetLastError();
		}

	std::cout << "Messages from Administrator:\n";
	for (size_t i = 0; i < n; ++i)
	{
		WaitForSingleObject(semaphore, INFINITE); // ожидание доступа 
		std::cout << "activ";
		int index = WaitForMultipleObjects(2, events, FALSE, INFINITE) - WAIT_OBJECT_0; // ожидание соощения от Administrator
		std::cout << msgs[index] << std::endl;
		ResetEvent(events[index]);
		ReleaseSemaphore(semaphore, 1, NULL);
		std::cout << "realise";
	}


	std::cout << "I'm done!\n";
	system("pause");
	for (size_t i = 0; i < 2; ++i)
		CloseHandle(events[i]);
	CloseHandle(semaphore);

	SetEvent(signal_event_from_reader);
	return 0;
}