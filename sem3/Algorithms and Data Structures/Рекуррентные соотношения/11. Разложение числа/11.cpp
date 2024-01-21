#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>

int main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long long a, b, c;
	fin >> a >> b >> c;

	long long result = 0;
	if (a < b) {
		result = -1;
	}
	else if (a <= c) {
		result = 1;
	}
	else {
		double squareRoot = sqrt(a) + 1;
		if (squareRoot < b) {
			result = -1;
		}
		else {
			std::vector<long long> divisors, divisors2;

			if (b != 1) {
				divisors.push_back(1);
			}

			for (long long i{ b }; i <= squareRoot; ++i) {
				if (a % i == 0) {
					divisors.push_back(i);
					divisors2.push_back(a / i);
				}
			}

			long long lastIndexInVector2 = divisors2.size() - 1;
			if (lastIndexInVector2 >= 0) {
				if (divisors2.back() == divisors.back()) {
					--lastIndexInVector2;
				}
			}

			while (lastIndexInVector2 >= 0) {
				divisors.push_back(divisors2[lastIndexInVector2]);
				--lastIndexInVector2;
			}

			if (divisors.back() != a) {
				divisors.push_back(a);
			}

			std::vector<long long> numbers(divisors.size(), 0);

			numbers[0] = (b == 1 ? 1 : 0);

			for (long long i{ 1 }; i < divisors.size(); ++i) {
				long long minNumber = a;
				if (divisors[i] >= b && divisors[i] <= c) {
					numbers[i] = 1;
				}
				else {
					for (long long j{ 0 }; j < i; ++j) {
						if (divisors[i] % divisors[j] == 0) {
							long long res = divisors[i] / divisors[j];
							if (res >= b && res <= c) {
								if (numbers[j] < minNumber) {
									minNumber = numbers[j];
								}
							}
						}
						numbers[i] = minNumber + 1;
					}
				}
			}
			result = numbers.back();
			}

		}
		if (result == 1 && a > c) {
			result = -1;
		}
		if (result >= a || result == 0) {
			result = -1;
		}

		fout << result;

		fin.close();
		fout.close();
		return 0;
	}