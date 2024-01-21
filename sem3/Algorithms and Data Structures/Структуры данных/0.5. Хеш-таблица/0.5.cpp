#include<iostream>
#include<vector>
#include<fstream>

long long getIndex(long long number, long long m, long long c, long long i) {
	return ((number % m) + c * i) % m;
}

int  main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long long  m, c, n;
	fin >> m >> c >> n;
	std::vector<long long> table(m, -1);

	for (size_t i{ 0 }; i < n; ++i) {
		long long number;
		fin >> number;

		long long j{ 0 };
		while (true) {
			long long index = getIndex(number, m, c, j);

			if (table[index] == -1 || table[index] == number) {
				table[index] = number;
				break;
			}
			++j;
		}
	}

	for (size_t i{ 0 }; i < table.size(); ++i) {
		fout << table[i] << " ";
	}
}
