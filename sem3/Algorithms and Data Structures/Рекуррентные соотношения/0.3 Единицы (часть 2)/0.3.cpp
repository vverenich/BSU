#include<iostream> 

constexpr int MOD = 1000000007;
long long Pow(long long n, int deg) {
	if (deg == 0) {
		return 1;
	}

	if (!(deg % 2)) {
		return Pow(n * n % MOD, deg / 2) % MOD;
	}

	return (n * (Pow(n, deg - 1))) % MOD;
}

long long multiplyNumbers(int first, int second) {
	long long result=1;

	for (int i{ first }; i <= second; ++i) {
		result = (result * i) % MOD;
	}

	return result;
}

long long getNumber(int N, int K) {
	long long numerator = multiplyNumbers(K+1, N);
	long long denominator = multiplyNumbers(1, N - K);

	denominator = Pow(denominator, MOD - 2);

	return ( numerator * denominator )% MOD;
 }

int main() {
	int N, K;
	std::cin >> N >> K;

	std::cout << getNumber(N, K);
}