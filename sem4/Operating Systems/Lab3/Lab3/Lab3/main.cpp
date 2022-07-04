#include <windows.h>
#include <iostream>
#include <vector>

CRITICAL_SECTION cs;
HANDLE hSignalEvent;

struct CustomArray
{
	unsigned m_A;
	unsigned m_B;

	std::vector<unsigned> m_array;
	unsigned m_productOfElements;
};

DWORD WINAPI workThreadFunc(LPVOID myArray)
{
	std::cout << "\n\n*Thread work is working*";

	EnterCriticalSection(&cs);
	Sleep(20);

	/**
	* Ask the user for the time interval required to rest
	* after cooking one element in array
	*/
	std::cout << "\n\tEnter time of sleeping: ";
	unsigned timeToSleep;
	std::cin >> timeToSleep;

	/**
	* Search in the array of elements from the range [m_A, m_B]
	* (place them in the array on the left, the remaining elements of
	* the array - padding with zeros)
	*/
	auto arr = static_cast<CustomArray*>(myArray);

	// Swapping the appropriate elements
	size_t indexOfElementToSwapWith{ 0 };
	for (size_t i{ 0 }; i < arr->m_array.size(); ++i)
	{
		if (arr->m_A <= arr->m_array.at(i) && arr->m_B >= arr->m_array.at(i))
		{
			std::swap(arr->m_array.at(indexOfElementToSwapWith), arr->m_array.at(i));
			++indexOfElementToSwapWith;
		}
	}

	// Zeroing of non-corresponding elements
	for (size_t i{ indexOfElementToSwapWith }; i < arr->m_array.size(); ++i)
	{
		arr->m_array.at(i) = 0;
	}

	/**
	* Printing final array with time to sleep, that was entered above
	*/
	Sleep(timeToSleep);
	std::cout << "\n\n\tArray information after work thread's task:";
	std::cout << "\n\t\tArray: ";
	for (size_t i{ 0 }; i < arr->m_array.size(); ++i)
	{
		std::cout << arr->m_array.at(i);
		if (i != arr->m_array.size() - 1)
		{
			std::cout << ", ";
			Sleep(timeToSleep);
		}
	}

	/**
	* Leaving critical section in order to MultElement thread start its work
	*/
	LeaveCriticalSection(&cs);

	std::cout << "\n\n*Thread work is not working anymore*";

	return 0;
}

DWORD WINAPI multElementThreadFunc(LPVOID myArray)
{
	std::cout << "\n\n*Thread MultElement is working*";

	/**
	* If the array is already prepared this thread enters the section
	*/
	EnterCriticalSection(&cs);

	auto arr = static_cast<CustomArray*>(myArray);
	arr->m_productOfElements = 1;
	for (size_t i{ 0 }; i < arr->m_array.size(); ++i) {
		if (arr->m_array.at(i) == 0)
		{
			break;
		}
		arr->m_productOfElements *= arr->m_array.at(i);
	}

	/**
	* Giving the signla to main thread to start its job
	*/
	SetEvent(hSignalEvent);

	LeaveCriticalSection(&cs);

	std::cout << "\n\n*Thread MultElement is not working anymore*";

	return 0;
}

int main()
{
	std::cout << "*Thread main is working*";
	/**
	* Critical section and event initialization
	*/
	InitializeCriticalSection(&cs);
	hSignalEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hSignalEvent == NULL)
	{
		return GetLastError();
	}

	/**
	* Creating the CustomArray object and filling its fields
	*/
	std::cout << "\n\n\tEnter the size of array: ";
	size_t arraySize;
	std::cin >> arraySize;

	CustomArray customArray;
	customArray.m_array.resize(arraySize);

	for (size_t i{ 0 }; i < arraySize; ++i) {
		std::cout << "\n\tEnter element number " << i << ": ";
		std::cin >> customArray.m_array.at(i);
	}

	std::cout << "\n\n\tEnter A: ";
	std::cin >> customArray.m_A;
	std::cout << "\n\tEnter B: ";
	std::cin >> customArray.m_B;

	/**
	* Printing the size of the array and the array itself
	*/
	std::cout << "\n\n\tArray information before work thread's job:";
	std::cout << "\n\t\tArray size: " << customArray.m_array.size();
	std::cout << "\n\t\tArray: ";
	for (size_t i{ 0 }; i < arraySize; ++i)
	{
		std::cout << customArray.m_array.at(i);
		if (i != arraySize - 1)
		{
			std::cout << ", ";
		}
	}

	/**
	* Creating the thread work and run it
	*/
	HANDLE hWorkThread, hMultElementThread;
	DWORD IDworkThread, IDmultElementThread;

	hWorkThread = CreateThread(NULL, 0, workThreadFunc, &customArray, 0, &IDworkThread);
	if (hWorkThread == NULL)
		return GetLastError();
	hMultElementThread = CreateThread(NULL, 0, multElementThreadFunc, &customArray, 0, &IDmultElementThread);
	if (hMultElementThread == NULL)
		return GetLastError();

	/**
	* Waiting for the MultElement thread to do its job
	*/
	WaitForSingleObject(hSignalEvent, INFINITE);
	std::cout << "\n\tThe product of elements that left in array: " << customArray.m_productOfElements;

	/**
	* Waiting for the work thread and MultElement thread to finish their work
	*/
	WaitForSingleObject(hWorkThread, INFINITE);
	WaitForSingleObject(hMultElementThread, INFINITE);

	/**
	* Close the critical section and handles
	*/
	DeleteCriticalSection(&cs);

	CloseHandle(hWorkThread);
	CloseHandle(hMultElementThread);

	CloseHandle(hSignalEvent);

	std::cout << "\n\n*Thread main is not working anymore*";
	return 0;
}
