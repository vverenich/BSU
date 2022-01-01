#include<iostream> 
#include<vector>
#include<fstream>
#include<set>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<numeric>

struct DSU {
	std::vector<size_t> numbers;
	std::vector<size_t> sizes;
	size_t components;

	DSU(size_t number) noexcept :components{number}  {
		numbers.resize(number + 1);
		std::iota(numbers.begin(), numbers.end(), 0);

		sizes.resize(number + 1);
		std::fill(sizes.begin(), sizes.end(), 1);
	}
	
	size_t findSet(size_t x) {
		if (x == numbers[x]) {
			return x;
		}

		numbers[x] = findSet(numbers[x]);
		return numbers[x];
	}

	void unionCities(size_t x, size_t y) {
		x = findSet(x);
		y = findSet(y);

		if (x != y) {
			--components;
			if (sizes[x] < sizes[y]) {
				std::swap(x, y);
			}
			sizes[x] += sizes[y];
			numbers[y] = x;
			
		}
	}
};

int main() {
	int n, m;

	FILE* fr, * fw;
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	fscanf(fr, "%d %d", &n, &m);

	int** array = new int* [n];
	for (size_t i{ 0 }; i < n; ++i) {
		array[i] = new int[n];
	}

	for (size_t i{ 0 }; i < n; ++i) {
		for (size_t j{ 0 }; j < n; ++j) {
			array[i][j] = 0;
		}
	}

	size_t first, second;

	for (int i{ 0 }; i < m; ++i) {
		//fin >> v1 >> v2;

		fscanf(fr, "%d %d", &first, &second);

		array[first-1][second-1] = 1;
		array[second-1][first-1] = 1;
	}


	for (size_t i{ 0 }; i < n; ++i) {
		for (size_t j{ 0 }; j < n; ++j) {
			fprintf(fw, "%d ", array[i][j]);
		}
		fprintf(fw, "\n");
	}
	//fin.close();
	//fout.close();

	fclose(fr);
	fclose(fw);

	for (size_t i{ 0 }; i < n; ++i) {
		delete[] array[i];
	}

	delete[] array;


	return 0;

}