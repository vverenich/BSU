#include<iostream> 
#include<vector>
#include<fstream>
#include<set>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<numeric>


int main() {
	int n;

	FILE* fr, * fw;
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	fscanf(fr, "%d", &n);
	/*
	int** array = new int* [n];
	for (size_t i{ 0 }; i < n; ++i) {
		array[i] = new int[n];
	}

	for (size_t i{ 0 }; i < n; ++i) {
		for (size_t j{ 0 }; j < n; ++j) {
			array[i][j] = 0;
		}
	}
	*/

	std::vector<int> vector(n,0);
	size_t value;
	for (size_t i{ 0 }; i < n * n; ++i) {
		fscanf(fr, "%d", &value);
		if (value) {
			vector[i%n] = i / n + 1;
		}
	}

	for (const auto& i : vector) {
		fprintf(fw, "%d ", i);
	}
	fclose(fr);
	fclose(fw);

	return 0;

}