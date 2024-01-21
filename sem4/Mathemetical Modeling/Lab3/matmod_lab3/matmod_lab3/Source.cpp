#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <limits.h>
#include <algorithm>
#include <math.h>
#include <time.h>

#define ep 2.0

#define sqr(x) (x)*(x)
using namespace std;

double rd() {
	int r = rand();
	while (r == 0 || r == RAND_MAX)
		r = rand();
	return (double)r / RAND_MAX;
}
/*
#define gm -5.0
#define gs 5
double gaussian() {
	return gm + gs * sqrt(-2 * log(rd())) * cos(2 * M_PI * rd());
}

#define lambda 0.5
#define hi_n 10
#define k (hi_n/2)
double hi() {
	////
	return -logistic_a + (-logistic_b) * log(1 / rd() - 1);
}

#define ep 2.0
double exponential() {
	return -log(rd()) / ep;
}
*/

#define lp 2.0
double laplace() {
	double y = rd();
	if (y < 0.5)
		return log(2 * y) / lp;
	return -log(2 * (1 - y)) / lp;
}



#define logistic_a 2.0
#define logistic_b 3.0
double logistic() {
	return -logistic_a + (-logistic_b) * log(1 / rd() - 1);
}



double E(double(*f)(), int n) {
	double summ = 0;
	for (int i = 0; i < n; ++i)
		summ += f();
	return summ / n;
}

double D(double(*f)(), int n) {
	double summ = 0;
	double _E = E(f, n);
	for (int i = 0; i < n; ++i)
		summ += pow(f() - _E, 2);
	return summ / (n - 1);
}

void printED(int n) {
	//cout << "\nhi^2 distribution:\n\t E = " << E(hi, n) << '(' << -2.0 << ")\n\t D = " << D(hi, n) << '(' << 30.5 << ')';
	//cout << "\ngaussian distribution:\n\t E = " << E(gaussian, n) << '(' << gm << ")\n\t D = " << D(gaussian, n) << '(' << gs * gs << ')';
	//cout << "\nexponential distribution:\n\t E = " << E(exponential, n) << '(' << 1 / ep << ")\n\t D = " << D(exponential, n) << '(' << 1 / (ep * ep) << ')';

	cout << "\nlogistic distribution:\n\t E = " << E(logistic, n) << '(' << -2.0 << ")\n\t D = " << D(logistic, n) << '(' << 29.4 << ')';
	cout << "\nlaplace distribution:\n\t E = " << E(laplace, n) << "(0.00)\n\t D = " << D(laplace, n) << '(' << 0.5 << ')';
}
/**
double Fgaussian(double x) {
	return (1 + erf((x - gm) / sqrt(2 * sqr(gs)))) / 2;
}

double Fexponential(double x) {
	return 1 - exp(-ep * x);
}

// gamma function with param k = 10 / 2
double gammaF(double x) {
	return pow(log(x), 4);
}

double Fhi(double x) {

	if (x < 0) {
		return 0;
	}
	else {
		return pow(lambda, k) * pow(x, k - 1) * exp(-lambda * x) / gammaF(x);
	}
}
*/
double Flaplace(double x) {
	if (x < 0)
		return exp(lp * x) / 2;
	return 1 - exp(-lp * x) / 2;
}



double Flogistic(double x) {
	return 1 / (1 + exp(-(x - logistic_a) / logistic_b));
}

double komogorov(double(*f)(), double(*F)(double), int n, double* arr)
{
	for (int i = 0; i < n; ++i)
		arr[i] = f();

	sort(arr, arr + n);
	double max = 0;
	for (int i = 0; i < n; ++i) {
		double b = abs(F(arr[i]) - (2 * (double)i + 1) / (2 * n));
		if (max < b)
			max = b;
	}
	return sqrt(n) * (max + 1 / (2 * n));
}

int map(int n, double x, double range_start, double range_end) {
	if (x < range_start)
		return 0;
	if (x > range_end)
		return n - 1;
	return (int)((n - 2) * (x - range_start) / (range_end - range_start)) + 1;
}

double pearson(double(*f)(), int* v, int L, int N, double range_start, double range_end, double* P) {
	for (int i = 0; i < L; ++i)
		v[i] = 0;
	for (int i = 0; i < N; ++i)
		v[map(L, f(), range_start, range_end)] += 1;
	double hi = 0;
	for (int i = 0; i < L; ++i)
		hi += sqr(v[i] - N * P[i]) / (N * P[i]);
	return hi;
}

void generateP(double(*F)(double), int L, double range_start, double range_end, double* P) {
	P[0] = F(range_start);
	for (int i = 1; i < L - 1; ++i)
		P[i] = F(range_start + (range_end - range_start) * i / (L - 2)) - F(range_start + (range_end - range_start) * (i - 1) / (L - 2));
	P[L - 1] = 1;
	for (int i = 0; i < L - 1; ++i)
		P[L - 1] -= P[i];
}

void printKolmogorovCheck(int n, int testcnt) {
	int laplaceKolmogorovCnt = 0;
	/**
	int gaussianKolmogorovCnt = 0;
	int exponentialKolmogorovCnt = 0;
	int hiKolmogorovCnt = 0;
	*/
	int logisticKolmogorovCnt = 0;
	
	double C = 0.24;
	double* arr = new double[n];
	for (int i = 0; i < testcnt; ++i) {
		/**
		if (C < komogorov(gaussian, Fgaussian, n, arr))
			++gaussianKolmogorovCnt;
		if (C < komogorov(hi, Fhi, n, arr))
			++hiKolmogorovCnt;
		if (C < komogorov(exponential, Fexponential, n, arr))
			++exponentialKolmogorovCnt;
		*/
		if (C < komogorov(logistic, Flogistic, n, arr))
			++logisticKolmogorovCnt;
		if (C < komogorov(laplace, Flaplace, n, arr))
			++laplaceKolmogorovCnt;
		
	}
	/*
	cout << "\nKolmogorov test gaussian:     " << gaussianKolmogorovCnt << '/' << testcnt;
	cout << "\nKolmogorov test exponential:  " << exponentialKolmogorovCnt << '/' << testcnt;
	cout << "\nKolmogorov test hi:  " << hiKolmogorovCnt << '/' << testcnt;
	*/
	cout << "\nKolmogorov test logistic:  " << logisticKolmogorovCnt << '/' << testcnt;
	cout << "\nKolmogorov test laplace:   " << laplaceKolmogorovCnt << '/' << testcnt;
}

void printPearsonCheck(int n, int testcnt) {
	/**
	int Lgaussian = 20;
	double Cgaussian = 5.1435;
	double* Pgaussian = new double[Lgaussian];
	int* Vgaussian = new int[Lgaussian];
	double range_start_gaussian = gm - 2 * gs;
	double range_end_gaussian = gm + 2 * gs;
	generateP(Fgaussian, Lgaussian, range_start_gaussian, range_end_gaussian, Pgaussian);
	int gaussianPearsonCnt = 0;
	for (int i = 0; i < testcnt; ++i)
		if (pearson(gaussian, Vgaussian, Lgaussian, n, range_start_gaussian, range_end_gaussian, Pgaussian) > Cgaussian)
			++gaussianPearsonCnt;
	
	int Lexponential = 20;
	double Cexponential = 5.1435;
	double* Pexponential = new double[Lexponential];
	int* Vexponential = new int[Lexponential];
	double range_start_exponential = 0.001;
	double range_end_exponential = log(ep);
	generateP(Fexponential, Lexponential, range_start_exponential, range_end_exponential, Pexponential);
	int exponentialPearsonCnt = 0;
	for (int i = 0; i < testcnt; ++i)
		if (pearson(exponential, Vexponential, Lexponential, n, range_start_exponential, range_end_exponential, Pexponential) > Cexponential)
			++exponentialPearsonCnt;

	int Lhi = 20;
	double Chi = 30.1435;
	double* Phi = new double[Lhi];
	int* Vhi = new int[Lhi];
	double range_start_hi = 0.001;
	double range_end_hi = log(ep);
	generateP(Fhi, Lhi, range_start_hi, range_end_hi, Phi);
	int hiPearsonCnt = 0;
	for (int i = 0; i < testcnt; ++i)
		if (pearson(hi, Vhi, Lhi, n, range_start_hi, range_end_hi, Phi) > Chi)
			++hiPearsonCnt;
	*/
	int Llaplace = 20;
	double Claplace = 0.89;
	double* Plaplace = new double[Llaplace];
	int* Vlaplace = new int[Llaplace];
	double range_start_laplace = -5 * lp;
	double range_end_laplace = 5 * lp;
	generateP(Flaplace, Llaplace, range_start_laplace, range_end_laplace, Plaplace);
	int laplacePearsonCnt = 0;
	for (int i = 0; i < testcnt; ++i)
		if (pearson(laplace, Vlaplace, Llaplace, n, range_start_laplace, range_end_laplace, Plaplace) > Claplace)
			++laplacePearsonCnt;

	int Llogistic = 20;
	double Clogistic = 10.1435;
	double* Plogistic = new double[Llogistic];
	int* Vlogistic = new int[Llogistic];
	double range_start_logistic = 0.001;
	double range_end_logistic = log(ep);
	generateP(Flogistic, Llogistic, range_start_logistic, range_end_logistic, Plogistic);
	int logisticPearsonCnt = 0;
	for (int i = 0; i < testcnt; ++i)
		if (pearson(logistic, Vlogistic, Llogistic, n, range_start_logistic, range_end_logistic, Plogistic) > Clogistic)
			++logisticPearsonCnt;
	/**
	cout << "\nPearson test gaussian:     " << gaussianPearsonCnt << '/' << testcnt;
	cout << "\nPearson test exponential:  " << exponentialPearsonCnt << '/' << testcnt;
	cout << "\nPearson test hi:  " << hiPearsonCnt << '/' << testcnt;
	*/
	cout << "\nPearson test logistic:  " << logisticPearsonCnt << '/' << testcnt;
	cout << "\nPearson test laplace:   " << laplacePearsonCnt << '/' << testcnt;
}

void print(double(*f)(), char* file, int cnt, int param) {
	ofstream fout(file);
	for (int i = 0; i < cnt; ++i)
		fout << f() << endl;
	fout.close();
	/**
	char* run = new char[100];
	strcpy(run, "python graph.py ");
	strcat(run, file);
	int pos = strlen(run);
	run[pos] = ' ';
	itoa(param, run + pos + 1, 10);
	system(run);
	*/
}

int main() {
	srand(time(0));
	printED(10000);
	cout << "\n\n";
	printPearsonCheck(1000, 1000);
	cout << "\n\n";
	printKolmogorovCheck(1000, 1000);

	//print(gaussian, "gaussian.txt", 10000, 50);
	//print(exponential, "exponential.txt", 10000, 20);
	print(laplace, "laplace.txt", 10000, 20);
	print(logistic, "logistic.txt", 10000, 20);
	//print(hi, "hi.txt", 10000, 20);
	cout << "\n";

	system("pause");
}
