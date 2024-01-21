#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <functional>
#include <fstream>

const double realValueVar4{ 3.21588 };
const double sigmaVar4{ 2 * M_PI };
double funcVar4(double x, double y)
{
	return 1 / (std::pow(x, 2) + std::pow(y, 4));
}

bool isPointBelongToIntegrationAreaVar4(double x, double y)
{
	return 1 <= std::pow(x, 2) + std::pow(y, 2) && std::pow(x, 2) + std::pow(y, 2) < 3;
}

double getRandZeroToOne()
{
	return rand() / (RAND_MAX + 1.0);
}

double getX(double z)
{
	const double a{ -std::sqrt(3) };
	const double A{ std::sqrt(3) };

	return a + (A - a) * z;
}

double getY(double z)
{
	const double a{ -std::sqrt(3) };
	const double A{ std::sqrt(3) };

	return a + (A - a) * z;
}

double calculateDefiniteIntegral(const std::function<double(double, double)> &func, const size_t N,
	std::ofstream &fout)
{
	double sum{ 0 };
	size_t m{ 0 };
	for (size_t i{ 0 }; i < N; ++i)
	{
		const double x{ getX(getRandZeroToOne()) };
		const double y{ getY(getRandZeroToOne()) };

		if (isPointBelongToIntegrationAreaVar4(x, y))
		{
			++m;
			sum += funcVar4(x, y);
			fout << abs(sum * sigmaVar4 / m - realValueVar4) << "\n";
		}


	}

	return sum * sigmaVar4 / m;
}

void doVar4()
{
	std::ofstream fout("delta.txt");
	const size_t N{ 10000 };

	std::cout << "**************************\n";
	std::cout << "Results for var 4:\n";
	std::cout << "**************************\n";
	std::cout << "Calculated value: " << calculateDefiniteIntegral(funcVar4, N, fout) << "\n";
	std::cout << "Real value:       " << realValueVar4 << "\n";
	std::cout << "Iteration count:  " << N << "\n";
	std::cout << "Accuracy:         " << 1.0 / sqrt(N) << "\n";
	std::cout << "**************************\n";

	fout.close();
}


int main() {
	doVar4();
}

