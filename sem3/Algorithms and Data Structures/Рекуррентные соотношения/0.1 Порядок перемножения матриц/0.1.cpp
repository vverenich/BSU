#include<iostream>
#include<fstream>
#include<vector>

long long getNumber(const std::vector<std::pair<int, int>> &v, int n) {
	long long **arr = new long long *[n];
	for (int i{ 0 }; i < n; ++i) {
		arr[i] = new long long[n];
	}

	for (int i{ 0 }; i < n; ++i) {
		arr[i][i] = 0;
	}
	for (int j{ 1 }; j < n; ++j) {
		for (int i{ 0 }; i < n; ++i) {
			if (i + j > n - 1) {
				i = n;
				continue;
			}
			arr[i][i + j] = LLONG_MAX;
			for (int t = 0; t < j; ++t) {
				int res = arr[i][i + t] + arr[i + 1 + t][i + j] + v[i].first * v[i + t].second * v[i + j].second;
				if (arr[i][i + j] > res) {
					arr[i][i + j] = res;
				}
			}
		}
	}

	long long result = arr[0][n - 1];
	for (int i{ 0 }; i < n; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
	return result;
}

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	int n;
	fin >> n;

	std::vector<std::pair<int, int>> vector(n);
	for (int i{ 0 }; i < n; ++i) {
		fin >> vector[i].first >> vector[i].second;
	}


	fout << getNumber(vector, n);

}