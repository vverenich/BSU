#include <thread>
#include <algorithm>
#include <iostream>
#include <vector>

const int gc_n = 100000;
const int gc_m = 1000;

int** g_A;
int* g_b;
int* g_result;

struct accumulate_block
{
	void operator()(const size_t first, const size_t last)
	{
		for (size_t i = first; i < last; ++i) {
			g_result[i] = 0;
			for (size_t j{ 0 }; j < gc_m; ++j) {
				g_result[i] += g_A[i][j] * g_b[j];
			}
		}
	}
};

void parallel_accumulate(const size_t n)
{
	unsigned long const length = n;

	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(max_threads, (hardware_threads != 0 ? hardware_threads : 2));
	unsigned long const block_size = gc_n / num_threads;

	std::cout << "number of threads: " << num_threads << "\n";

	std::vector<std::thread> threads(num_threads - 1);
	size_t block_start = 0;
	for (unsigned long i = 0; i < (num_threads - 1); ++i) {
		size_t block_end = block_start;
		block_end += block_size;
		threads[i] = std::thread(
			accumulate_block(),
			block_start, block_end);
		block_start = block_end;
	}

	accumulate_block()(block_start, n);

	for (auto& entry : threads) {
		entry.join();
	}
}

void InitMatrixRand(int** B, int size1, int size2)
{
	int i, j;
	srand(time(0));
	for (i = 0; i < size1; ++i) {
		for (j = 0; j < size2; ++j) {
			B[i][j] = rand() % 10;
			//std::cout << B[i][j] << "\t";
		}
		//std::cout << "\n";
	}
}

void InitVectorRand(int* B, int size)
{
	int i;
	srand(time(0));
	for (i = 0; i < size; ++i) {
		B[i] = rand() % 10;
		//std::cout << B[i] << "\n";
	}
}

void doLab()
{
	// Allocate memory
	g_A = new int* [gc_n];
	g_b = new int[gc_m];
	g_result = new int[gc_n];

	for (int i = 0; i < gc_n; ++i) {
		g_A[i] = new int[gc_m];
	}

	// Initialize matrix, vector
	InitMatrixRand(g_A, gc_n, gc_m);
	InitVectorRand(g_b, gc_m);

	clock_t start = clock();

	parallel_accumulate(gc_n);

	clock_t end = clock();

	printf("time elapsed: %.16f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

	/*
	// Print result vector
	for (size_t i{ 0 }; i < gc_n; ++i) {
		std::cout << g_result[i] << "\n";
	}
	*/

	// Deallocate memory
	for (int i = 0; i < gc_n; ++i) {
		delete[] g_A[i];
	}
	delete[] g_b;
	delete[] g_result;
	delete[] g_A;
}

int main()
{
	doLab();

	return 0;
}