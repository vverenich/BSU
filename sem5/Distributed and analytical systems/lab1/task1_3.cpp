#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

#define p 5 // количество дочерних потоков
double pi[p];
int n = 1'000'000;

DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	int nParam = (int)pvParam;
	std::cout << "\n" << nParam;
	int i, start;
	double h, sum, x;
	h = 1. / n;
	sum = 0.;
	start = nParam;
	for (i = start; i < n; i += p)
	{
		x = h * i;
		sum += 4.0 / (1. + x * x);
	}
	pi[nParam] = h * sum;
	return 0;
}

int main()
{
	HANDLE hThreads[p];
	int k;
	double sum;

	StartCounter();

	// создание дочерних потоков
	for (k = 0; k < p; ++k)
	{
		hThreads[k] = (HANDLE)CreateThread(NULL, 0,
			ThreadFunction, (LPVOID)k, 0, NULL);
		if (hThreads[k] == NULL) // обработка ошибки
		{
			printf("Create Thread %d Error=%d\n", k, GetLastError());
			return -1;
		}
	}
	// ожидание завершения дочерних потоков
	WaitForMultipleObjects(p, hThreads, TRUE, INFINITE);
	for (k = 0; k < p; ++k)
		CloseHandle(hThreads[k]);
	sum = 0.;
	for (k = 0; k < p; ++k)
		sum += pi[k];
	printf("PI = %.16f\n", sum);

	printf("\nTime elapsed: %.16f", GetCounter());

	return 0;
}
