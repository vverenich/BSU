#define _USE_MATH_DEFINES
#define NOMINMAX
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>
#include <functional>
#include <cmath>
#include <thread>
#include <vector>
#include <limits>
#include <numeric>

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

const int    g_n = 100'000;
const double g_a = 0;
const double g_b = 7;

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

template<typename T>
struct accumulate_block
{
	void operator()(const size_t first, const size_t last, T& result)
	{
		double h = (g_b - g_a) / g_n;
		double sum = 0.0;
		double x;

		for (size_t i = first; i < last; ++i) {
			x = h * i;
			sum += func1(x);
		}

		result = h * sum;
	}
};

template<typename T>
T parallel_accumulate(const size_t n)
{
	unsigned long const length = n;

	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(max_threads, (hardware_threads != 0 ? hardware_threads : 2));
	unsigned long const block_size = length / num_threads;

	std::cout << "number of threads: " << num_threads << "\n";

	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1);
	size_t block_start = 0;
	for (unsigned long i = 0; i < (num_threads - 1); ++i) {
		size_t block_end = block_start;
		block_end += block_size;
		threads[i] = std::thread(
			accumulate_block<T>(),
			block_start, block_end, std::ref(results[i]));
		block_start = block_end;
	}
	accumulate_block<T>()(block_start, n, results[num_threads - 1]);
	for (auto& entry : threads) {
		entry.join();
	}

	return std::accumulate(results.begin(), results.end(), 0.0);
}

int main()
{
	StartCounter();
	
	double sum = parallel_accumulate<double>(g_n);
	
	printf("result = %.16f\n", sum);
	printf("\nTime elapsed: %.16f", GetCounter());

	return 0;
}
