#define _USE_MATH_DEFINES

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <cmath>



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

const size_t g_p = 4;
double       g_pi[g_p];
const int    g_n = 100'000;

const double g_a = 0;
const double g_b = 3;

double func2(double x)
{
	return cos(x);
}

double func1(double x)
{
	return x * x;
}

double func3(double x)
{
	return sqrt(x);
}

struct DefiniteIntegralParams {
	DefiniteIntegralParams(double a, double b, double numberOfThread)
	{
		m_a = a;
		m_b = b;
		m_numberOfThread = numberOfThread;
	}

	double m_a;
	double m_b;	
	size_t m_numberOfThread;
};

DWORD WINAPI ThreadFunction(LPVOID pvParam)
{
	size_t nParam = (int)pvParam;
	size_t start = nParam;
	size_t i;
	double h = (g_b - g_a) / g_n;
	double sum = 0.0;
	double x;

	for (i = start; i < g_n; i += g_p)
	{
		x = h * i;
		sum += func3(x);
	}
	g_pi[nParam] = h * sum;

	return 0;
}

int main()
{
	HANDLE hThreads[g_p];
	size_t k;
	double sum;


	StartCounter();

	// создание дочерних потоков
	for (k = 0; k < g_p; ++k)
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
	WaitForMultipleObjects(g_p, hThreads, TRUE, INFINITE);
	for (k = 0; k < g_p; ++k)
		CloseHandle(hThreads[k]);
	sum = 0.;
	for (k = 0; k < g_p; ++k)
		sum += g_pi[k];
	
	printf("PI = %.16f\n", sum );

	printf("\nTime elapsed: %.16f", GetCounter());

	return 0;
}
