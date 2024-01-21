#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>

// Real value for the definite integral [0, 5*pi / 7] of the following function
const double realValueVar4{ -0.485736 };
double funcVar4(double x)
{
	return cos(x + sin(x));
}

double getRandZeroToOne()
{
	return rand() / (RAND_MAX + 1.0);
}

double getXi(const double a, const double b)
{
	return a + getRandZeroToOne() * (b - a);
}

double calculateDefiniteIntegral(const std::function<double(double)>& func, 
								 const double a, const double b, const size_t N,
								 std::ofstream &fout)
{
	double result{ 0 };
	for (size_t i{ 0 }; i < N; ++i)
	{
		result += func(getXi(a, b));
		fout << abs((b - a) * result / N - realValueVar4) << "\n";
		
	}

	return (b - a) * result / N;
}
 void doVar4()
{
	std::ofstream fout("delta.txt");
	const double a{ 0 };
	const double b{ 5 * M_PI / 7 };
	const size_t N{ 100 };

	std::cout << "**************************\n";
	std::cout << "Results for var 4:\n";
	std::cout << "**************************\n";
	std::cout << "Calculated value: " << calculateDefiniteIntegral(funcVar4, a, b, N, fout) << "\n";
	std::cout << "Real value:       " << realValueVar4 << "\n";
	std::cout << "Iteration count:  " << N << "\n";
	std::cout << "Accuracy:         " << 1.0 / sqrt(N) << "\n";
	std::cout << "**************************\n";
}


int main() {
	doVar4();
}