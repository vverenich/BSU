#include<iostream>

long long getNumber(int n, int k) {
	long long** arr = new long long* [n+1];
	for (int i{ 0 }; i < n+1; ++i) {
		arr[i] = new long long [k+1];
	}
	for (int i{ 0 }; i < k+1; ++i) {
		arr[i][i] = 1;
	}
	for (int i{0}; i < n+1; ++i) {
		arr[i][0] = 1;
	}

	for (int i{ 0 }; i < n+1; ++i) {
		for (int j{ 1 }; j < i&&j<k+1; ++j) {
			if (j - 1 >= 0 && i - 1 >= 0) {
				arr[i][j] = (arr[i - 1][j - 1] + arr[i - 1][j]) % 1000000007;
			}
		}
	}

	long long result = arr[n][k];


	for (int i{ 0 }; i < n+1; ++i) {
		delete[] arr[i];
	}
	delete[] arr;

	return result;
}
int main() {

	int N, K;
	std::cin >> N>>K;


	std::cout<<getNumber(N,K);

}