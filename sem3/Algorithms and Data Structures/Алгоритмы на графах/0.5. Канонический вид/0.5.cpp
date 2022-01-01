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

	std::vector<size_t> vector(n, 0);

	size_t first, second;

	for (size_t i{ 0 }; i < n-1; ++i) {
		fscanf(fr, "%d %d", &first, &second);

		vector[second-1] = first;
	}

	for (const auto& i : vector) {
		fprintf(fw, "%d ", i);
	}
	//fin.close();
	//fout.close();

	fclose(fr);
	fclose(fw);


	return 0;

}