#include <iostream>
#include <fstream>
#include <limits.h>
#include <math.h>
#include <time.h>
#define printcnt 10000
#define tests 5000
int a0 = 262147;
int b = a0;
unsigned int M = 2147483648;

unsigned int curr_rand = a0;
double rand1() {
	return (double)rand() / RAND_MAX;
}

int geom_rand(double p) {
	return ceil(log(rand1()) / log(1 - p)) - 1;
}
/**
int poisson_rand(double param) {
	int k = 0;
	double prod = rand1();
	double expparam = exp(-param);
	while (prod > expparam) {
		prod *= rand1();
		++k;
	}
	return k;
}
*/

int binomial_rand(double p) {
	return (p - rand1()) >= 0 ? 1 :0;
}

double E(int(*f)(double), double param, int n) {
	double summ = 0;
	for (int i = 0; i < n; ++i)
		summ += f(param);
	return summ / n;
}

double D(int(*f)(double), double param, int n) {
	double summ = 0;
	double _E = E(f, param, n);
	for (int i = 0; i < n; ++i)
		summ += pow(f(param) - _E, 2);
	return summ / (n - 1);
}

double pirson_criterium(int(*f)(double), double param, int n, double* P, int L) {
	int* v = new int[L];
	double hi = 0;
	for (int i = 0; i < L; ++i)
		v[i] = 0;
	for (int i = 0; i < n; ++i) {
		int rd = f(param);
		if (rd >= 0) {
			v[rd < L ? rd : L - 1] += 1;
		}
	}
	for (int i = 0; i < L; ++i)
		hi += pow((v[i] - P[i] * n), 2) / (n * P[i]);
	return hi;
}
/**
double* generate_P_poisson(double param, int L) {
	double* P = new double[L];
	P[0] = 1;
	P[L - 1] = 1;
	for (int i = 1; i < L - 1; ++i)
		P[i] = param;
	for (int i = 2; i < L - 1; ++i)
		P[i] *= P[i - 1] / i;
	for (int i = 0; i < L - 1; ++i)
		P[i] *= exp(-param);
	for (int i = 0; i < L - 1; ++i)
		P[L - 1] -= P[i];
	return P;
}
*/
double* generate_P_geom(double param, int L) {
	double* P = new double[L];
	P[0] = param;
	P[L - 1] = 1;
	for (int i = 1; i < L - 1; ++i)
		P[i] = 1 - param;
	for (int i = 2; i < L - 1; ++i)
		P[i] *= P[i - 1];
	for (int i = 1; i < L - 1; ++i)
		P[i] *= param;
	for (int i = 0; i < L - 1; ++i)
		P[L - 1] -= P[i];
	return P;
}
//1; n / 1; n* (n - 1)/(1*2)
double* generate_P_binomial(double p, int L) {
	double* P = new double[L];
	P[0] = 1;
	P[L - 1] = 1;
	for (size_t i{ 1 }; i < L-1; ++i) {
		P[i] = P[i - 1] * (L - i - 1) / (i);
	}

	for (size_t i{ 0 }; i < L - 1; ++i)
	{
		P[L - 1] -= P[i];
	}
	return P;
}

int main() {
	srand(time(NULL));
	int L = 4;
	int n = 5000;
	double geom_param = 0.6;
	//double poisson_param = 0.7;
	double binomial_param = 0.2;
	double C1 = 21.5689;
	double C2 = 7.8147;

	int geom_count = 0;
	//int poisson_count = 0;
	int binomial_count = 0;
	
	for (int i = 0; i < tests; ++i) {
		if (pirson_criterium(geom_rand, geom_param, n, generate_P_geom(geom_param, L), L) < C1)
			geom_count++;
		if (pirson_criterium(binomial_rand, binomial_param, n, generate_P_binomial(binomial_param, L), L) < C2)
			binomial_count++;
	}
	std::cout << "Geom Pirson criterium: " << geom_count << "/" << tests;
	std::cout << "\nBinomial Pirson criterium: " << binomial_count << "/" << tests;
	std::cout << "\n\nGeom E = " << E(geom_rand, geom_param, n) << " | Real E = " << (1 - geom_param) / geom_param;
	std::cout << "\nBinomial E = " << E(binomial_rand, binomial_param, n) << " | Real E = " << binomial_param;

	std::cout << "\n\nGeom D = " << D(geom_rand, geom_param, n) << " | Real D = " << (1 - geom_param) / (geom_param * geom_param);
	std::cout << "\nBinomial D = " << D(binomial_rand, binomial_param, n) << " | Real D = " << binomial_param << std::endl;

	std::ofstream binomial_out("binomial.txt");
	std::ofstream geom_out("geom.txt");
	for (int i = 0; i < printcnt; ++i) {
		binomial_out << binomial_rand(binomial_param) << std::endl;
		geom_out << binomial_rand(binomial_param) << std::endl;
	}

	binomial_out.close();
	geom_out.close();
}