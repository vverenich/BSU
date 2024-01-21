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
	//std::ifstream fin("input.txt");
	//std::ofstream fout("output.txt");

	int n, q;
	//fin >> n >> q;

	FILE* fr, * fw;
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	fscanf(fr, "%d %d", &n, &q);

	DSU dsu(n);

	size_t first, second;
	for (int i{ 0 }; i < q; ++i) {
		//fin >> v1 >> v2;

		fscanf(fr, "%d %d", &first, &second);

		dsu.unionCities(first, second);
		fprintf(fw, "%d\n", dsu.components);
	}

	//fin.close();
	//fout.close();

	fclose(fr);
	fclose(fw);

	return 0;

}