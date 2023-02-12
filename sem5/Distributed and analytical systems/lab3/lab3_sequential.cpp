#include <windows.h>
#include <process.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>

const int gc_n = 100000;
const int gc_m = 1000;

int** g_A;
int* g_b;
int* g_result;

// Function calculates only one element in result vector
void calculateResultVectorElement(LPVOID pvParam)
{
	int i = (int)pvParam;
	g_result[i] = 0;
	for (size_t j{ 0 }; j < gc_m; ++j) {
		g_result[i] += g_A[i][j] * g_b[j];
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

	// Initialize matrix and vector
	InitMatrixRand(g_A, gc_n, gc_m);
	InitVectorRand(g_b, gc_m);

	clock_t start = clock();

	for (int i = 0; i < gc_n; ++i) {
		calculateResultVectorElement((LPVOID)i);
	}

	

	/*
	// Print result vector
	for (size_t i{ 0 }; i < gc_m; ++i) {
		std::cout << g_result[i] << "\n";
	}
	*/
	
	///Sleep(1000);
	clock_t end = clock();

	printf("time elapsed: %.16f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

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