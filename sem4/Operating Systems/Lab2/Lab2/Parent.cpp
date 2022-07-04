#include <windows.h>	
#include <process.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

struct CustomArray {
	std::vector<unsigned> m_array;
	unsigned			  m_A;
	unsigned			  m_B;

	std::wstring getCMDArguments() {
		std::wstring argument = L"Child.exe";

		argument += L" " + std::to_wstring(m_array.size());
		for (const auto& i : m_array) {
			argument += L" " + std::to_wstring(i);
		}
		argument += L" " + std::to_wstring(m_A) + L" " + std::to_wstring(m_B);

		return argument;
	}
};

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

	std::cout << "Enter A and B: ";
	std::cin >> myArray.m_A >> myArray.m_B;


	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	//set  screen buffer width to 300
	si.dwXCountChars = 140;

	/**
	//set the width and the height of the window
	si.dwYSize = 500;
	si.dwXSize = 500;
	*/

	//in order to apply all the changes above
	si.dwFlags = /*STARTF_USESIZE */ STARTF_USECOUNTCHARS  ;

	if (!CreateProcess(NULL,										  // No module name (use command line)
		const_cast<LPWSTR>(myArray.getCMDArguments().c_str()),        // Command line
		NULL,														  // Process handle not inheritable
		NULL,													      // Thread handle not inheritable
		FALSE,														  // Set handle inheritance to FALSE
		CREATE_NEW_CONSOLE,											  // No creation flags
		NULL,														  // Use parent's environment block
		NULL,														  // Use parent's starting directory 
		&si,														  // Pointer to STARTUPINFO structure 
		&pi)														  // Pointer to PROCESS_INFORMATION structure
		)

	{
		printf("CreateProcess failed (%d).\n", GetLastError());
	}

	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;

}