#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <functional>

double getRand0_1()
{
	return rand() / (RAND_MAX + 1.0);
}

double getRandomXi(const double a, const double b)
{
	return a + getRand0_1() * (b - a);
}

// Real value for the definite integral [18, 19] of the following function
const double realValueVar18{ 1.26341 };
double funcVar18(double x)
{
	return std::atan(std::pow(9 * x * x - 1, 1.0 / 7));
}

double calculateDefiniteIntegral(const std::function<double(double)>& func,
	const double a, const double b, const size_t N)
{
	// Iterations
	std::ofstream fout_X("X.txt");
	// Difference between iteration approximation and exact value
	std::ofstream fout_Y("Y.txt");

	double result{ 0 };
	for (size_t i{ 0 }; i < N; ++i)
	{
		fout_X << i << "\n";
		result += func(getRandomXi(a, b));
		fout_Y << abs(realValueVar18 - result * (b - a) / N) << "\n";
	}

	return (b - a) * result / N;
}



int main() {
	const double a{ 18 };
	const double b{ 19 };
	const double N{ 100 };

	std::cout << "Results for var 18:\n";
	std::cout << "\tCalculated value: " << calculateDefiniteIntegral(funcVar18, a, b, N) << "\n";
	std::cout << "\tReal value:       " << realValueVar18 << "\n";
	std::cout << "\tIteration count:  " << N << "\n";
	std::cout << "\tAccuracy:         " << 1.0 / sqrt(N);
}