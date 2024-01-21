#include<iostream> 
#include<vector>
#include<fstream>
#include<set>
#include<algorithm>
#include <stdio.h>
#include <stdlib.h>
#include<numeric>
#include<list>


int main() {
	int n,m;

	FILE* fr, * fw;
	fr = fopen("input.txt", "r");
	fw = fopen("output.txt", "w");

	fscanf(fr, "%d %d", &n, &m);

	std::vector<std::list<int>> vector(n);

	size_t first, second;
	
	for (size_t i{ 0 }; i < m; ++i) {
		fscanf(fr, "%d %d", &first, &second);

		vector[first-1].push_back(second);
		vector[second-1].push_back(first);
	}

	for (size_t i{ 0 }; i < n;++i) {
		
		fprintf(fw, "%d ", vector[i].size());
		for (const auto& j: vector[i]) {
			fprintf(fw, "%d ", j);
		}
		fprintf(fw, "\n");
	}
	fclose(fr);
	fclose(fw);

	return 0;

}