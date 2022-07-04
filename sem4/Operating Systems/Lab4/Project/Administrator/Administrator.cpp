#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

int get_amount(std::string&& msg);

void CloseHandles(HANDLE mutex, HANDLE semaphore, HANDLE* events_reader, int size = 2);

void AddProcessDataToVector(std::vector<std::pair<STARTUPINFO, PROCESS_INFORMATION>>& vec, wchar_t* title);

void CloseProcesses(std::vector<std::pair<STARTUPINFO, PROCESS_INFORMATION>>& vec);

int main()
{
	std::vector<std::pair<STARTUPINFO, PROCESS_INFORMATION>> readers, writers;

	HANDLE mutex; // синхронизация Writer
	HANDLE semaphore; // события-сообщения для Reader
	HANDLE events_for_readers[2]; // события-сообщения для Administrator
	HANDLE signal_event_from_writer;
	HANDLE signal_event_from_reader;
	const char* msgs[] = { "A", "B" }; // массив для вывода в консоль сообщения
																	  // по индексу, используя WaitForMultipleObjects

	int processes_n, messages_n; // количество процессов, сообщения для одного процесса

	processes_n = get_amount("Enter amount of readers and writers: ");
	if (processes_n <= 0 || processes_n > 10)
	{
		std::cerr << "Wrong data\n";
		return -1;
	}

	messages_n = get_amount("Enter amount of messages: ");
	if (messages_n <= 0)
	{
		std::cerr << "Wrong data\n";
		return -2;
	}

	readers.reserve(processes_n);
	writers.reserve(processes_n);

	mutex = CreateMutex(NULL, FALSE, L"writer_mutex");
	semaphore = CreateSemaphore(NULL, 2, 2, L"reader_semaphore");

	events_for_readers[0] = CreateEvent(NULL, TRUE, FALSE, L"A_writer");
	events_for_readers[1] = CreateEvent(NULL, TRUE, FALSE, L"B_writer");

	signal_event_from_writer = CreateEvent(NULL, FALSE, FALSE, L"signal_from_writer");
	signal_event_from_reader = CreateEvent(NULL, FALSE, FALSE, L"signal_from_reader");

	std::wstring reader_cmd_str = L"Reader.exe " + std::to_wstring(messages_n);
	std::wstring writer_cmd_str = L"Writer.exe " + std::to_wstring(messages_n); // формирование командных строк для процессов,
																	   // второй аргумент - количество сообщений

	for (size_t i = 0; i < processes_n; ++i)
	{
		std::wstring first_reader_title = L"FirstReader " + std::to_wstring(i + 1);
		std::wstring second_reader_title = L"SecondReader " + std::to_wstring(i + 1);
		std::wstring writer_title = L"Writer " + std::to_wstring(i + 1);

		AddProcessDataToVector(readers, const_cast<wchar_t*>(first_reader_title.c_str()));
		AddProcessDataToVector(readers, const_cast<wchar_t*>(second_reader_title.c_str()));
		AddProcessDataToVector(writers, const_cast<wchar_t*>(writer_title.c_str()));


		if (!CreateProcess(NULL, const_cast<wchar_t*>(reader_cmd_str.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &readers[readers.size() - 2].first, &readers[readers.size() - 2].second) ||
			!CreateProcess(NULL, const_cast<wchar_t*>(writer_cmd_str.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &writers.back().first, &writers.back().second) ||
			!CreateProcess(NULL, const_cast<wchar_t*>(reader_cmd_str.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &readers[readers.size() - 1].first, &readers[readers.size() - 1].second))
		{
			std::cerr << "Fail to create a process\n";

			system("pause"); // в случае неудачи создания процесса - завершение работы
			CloseHandles(mutex, semaphore, events_for_readers);
			CloseProcesses(readers);
			CloseProcesses(writers);
			return GetLastError();
		}
	}

	std::cout << "Messages from Writers( and Readers):\n";
	for (int i = 0; i < processes_n; ++i) {
		int index = WaitForMultipleObjects(2, events_for_readers, FALSE, INFINITE) - WAIT_OBJECT_0; // ожидание сообщения от Writer
		std::cout << "Message: " << msgs[index] << "\n";
		WaitForSingleObject(signal_event_from_writer, INFINITE);
		std::cout << "Writer finished work" << "\n";
		for (int i = 0; i < 2; ++i) {
			WaitForSingleObject(signal_event_from_reader, INFINITE);
			std::cout << "Reader[" << i << "] finished work" << "\n";
		}
	}

	std::cout << "Program is over\n";
	CloseHandles(mutex, semaphore, events_for_readers);
	CloseHandle(signal_event_from_reader);
	CloseHandle(signal_event_from_writer);
	CloseProcesses(readers);
	CloseProcesses(writers);
	return 0;
}



int get_amount(std::string&& msg) //функция для получения количества из консоли
{
	int N;
	std::string buff;
	std::cout << msg << std::endl;
	std::getline(std::cin, buff);
	return atoi(buff.c_str());
}

void CloseHandles(HANDLE mutex, HANDLE semaphore, HANDLE* events_reader, int size) // функция для закрытия дескрипторов
{
	CloseHandle(mutex);
	CloseHandle(semaphore);
	for (size_t i = 0; i < size; ++i)
	{
		CloseHandle(events_reader[i]);
	}
}

void AddProcessDataToVector(std::vector<std::pair<STARTUPINFO, PROCESS_INFORMATION>>& vec, wchar_t* title) // добавление в вектор данных о процессе
{																										   // и добавление названия консоли 
	vec.push_back(std::make_pair<STARTUPINFO, PROCESS_INFORMATION>(STARTUPINFO(), PROCESS_INFORMATION()));

	ZeroMemory(&(vec.back().first), sizeof(vec.back().first));
	ZeroMemory(&(vec.back().first), sizeof(vec.back().second));

	vec.back().first.cb = sizeof(vec.back().first);
	vec.back().first.lpTitle = title;
}

void CloseProcesses(std::vector<std::pair<STARTUPINFO, PROCESS_INFORMATION>>& vec) // функция закрытия процессов
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		CloseHandle(vec[i].second.hThread);
		CloseHandle(vec[i].second.hProcess);
	}
}