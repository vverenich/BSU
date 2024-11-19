#include <iostream>
#include <iomanip>
#include <utility>

const double PI = std::acos(-1);
double f1(double x) {
	double res = std::sqrt(std::pow(2, x) - 1);
	return res;
}

double f2(double x) {
	double res = (x * x - 1) * std::pow(10, (-2) * x);
	return res;
}

double f3(double x) {
	double res = std::pow(std::tan(x / 2 + PI / 4), 3);
	return res;
}

std::pair<double, int> integral(double eps, int N, double (*function)(double), double a, double b) {

	double previousVal = 0;
	double presVal = (function(a) + function(b)) * (std::abs(a - b)) / 2;
	while (std::abs(presVal - previousVal) > eps) {
		N <<= 1;
		double n1 = a;
		double n2 = a + std::abs(a - b) / N;
		previousVal = presVal;
		presVal = 0;
		for (int i = 0; i < N; ++i) {
			presVal += (function(n1) + function(n2)) * (std::abs(n1 - n2)) / 2;
			n1 += std::abs(a - b) / N;
			n2 += std::abs(a - b) / N;
		}
	}
	return { presVal, N };
}
double getValue() {
	while (true) {
		std::cout << "Enter colculation accuracy(number in an interval from 10^(-1) to 10^(-7)): ";
		double eps;
		std::cin >> eps;
		if (std::cin.fail() || eps < 0.0000001 || eps > 0.1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "\nYou made an illegal choice.";
		}
		else {
			return eps;
		}
	}
}
int main() {
	double eps = getValue();
	std::pair<double, int> finishValue = integral(eps, 1, f1, 0.3, 1.0);
	std::cout << "- Value number 1 is " << std::setprecision(7) << finishValue.first << ", when N = " << finishValue.second;
	finishValue = integral(eps, 1, f2, 0, 0.4);
	std::cout << "\n- Value number 2 is " << std::setprecision(7) << finishValue.first << ", when N = " << finishValue.second;
	finishValue = integral(eps, 1, f3, 0, PI / 4);
	std::cout << "\n- Value number 3 is " << std::setprecision(7) << finishValue.first << ", when N = " << finishValue.second;
	return 0;
}
