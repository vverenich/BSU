#include<iostream>
#include<vector>
#include<fstream>

long long getNumber(long long n, long long m) {
	/*if (n == 1 && m == 1) {
		return 0;
	}*/
	std::vector<long long> arr(n, 1);
	for (int i{ 1 }; i < m; ++i) {
		for (int j{ 1 }; j < n; ++j) {
			arr[j] = (arr[j - 1] + arr[j])% 1000000007;
		}
	}
	return arr[n - 1];
}

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	int n = 0, m = 1;

	fin >> n >> m;
	fout << getNumber(n, m);

}