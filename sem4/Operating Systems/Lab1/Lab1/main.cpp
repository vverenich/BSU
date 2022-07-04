#include <windows.h>	
#include <process.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct CustomArray {
	std::vector<int> m_array;
	int			     m_maxValue;
};

UINT WINAPI findMax(LPVOID data)
{
	auto myArray = static_cast<CustomArray*>(data);
	myArray->m_maxValue = INT32_MIN;
	myArray->m_maxValue = *std::max_element(myArray->m_array.begin(), myArray->m_array.end());
	return 0;
}



int main()
{
	std::cout << "Enter the size of array: ";
	int size;
	std::cin >> size;

	CustomArray myArray;
	myArray.m_array.resize(size);

	for (size_t i{ 0 }; i < size; ++i) {
		std::cout << "\nEnter element number " << i << ": ";
		std::cin >> myArray.m_array[i];
	}

	std::cout << "\n\nEnter time to sleep(ms): ";
	int timeToSleep;
	std::cin >> timeToSleep;

	HANDLE workerThread;
	unsigned IDThread;
	workerThread = (HANDLE)_beginthreadex(NULL, 0, findMax, &myArray, 0, &IDThread);
	if (workerThread == NULL) {
		return GetLastError();
	}

	SuspendThread(workerThread);
	std::cout << "\nThread is suspended...";
	Sleep(timeToSleep);
	ResumeThread(workerThread);
	std::cout << "\nThread is resumed.";
	std::cout << "\nTime elapsed(ms): " << timeToSleep;

	//WaitForSingleObject(workerThread, INFINITE);
	CloseHandle(workerThread);	

	std::cout << "\nReturned value: " << myArray.m_maxValue;
	return 0;
}
