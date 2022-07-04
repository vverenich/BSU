
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>

double KolmogorovTest(double* a, int n)
{
	std::sort(a, a + n);
	int i = 0;
	double D = 0;
	for (i = 0; i < n; i++)
	{
		if (D < fabs(((double)(i + 1)) / n - a[i]))
			D = fabs(((double)(i + 1)) / n - a[i]);
	}
	std::cout << "Kolmogorov test result: D = " << D << " < 1.36\n";
	return D;
}

double PirsonTest(double* a, int n, int k)
{
	std::sort(a, a + n);
	int i = 0;
	int count = 0, j = 0;
	double xi2 = 0;
	for (j = 1; j <= k; j++)
	{
		count = 0;
		while ((a[i] < ((double)j) / k) & (i <= n))
		{
			i++;
			count++;
		}

		xi2 += (count - ((double)n) / k) / (((double)n) * k);


	}
	std::cout << "Pirson test result: xi2 = " << xi2 << " < 16.9\n";
	return xi2;
}

int main()
{
	std::ofstream foutMC("outputMC.txt");
	std::ofstream foutMM("outputMM.txt");

	constexpr unsigned long M{ 2'147'483'648 };
	constexpr int n{ 1'000 };
	constexpr long NN{ 1'000'000 };

	constexpr unsigned long beta{ 79'507 };
	constexpr unsigned K{ 64 };

	//Generation of the first sample by the multiplicative congruent method.
	unsigned long* x = new unsigned long[NN];
	x[0] = beta;
	double* b = new double[n];
	b[0] = ((double)x[0]) / M;

	long i;
	long j;

	foutMC << "Mult-Congr:\n";
	for (i = 0; i < n; i++)
	{
		x[i] = (beta * x[i - 1]) % M;
		b[i] = ((double)x[i]) / M;
		foutMC << b[i] << "\n";
	}

	std::cout << "Multi-Congruent sensor\n";
	std::cout << "**********************************\n";
	KolmogorovTest(b, n);
	PirsonTest(b, n, K);
	std::cout << "**********************************\n";




	//Generation of the second sample by the multiplicative congruent method.
	unsigned long beta2 = 4 * beta + 1;
	x[0] = beta2;
	double* c = new double[NN];
	c[0] = ((double)x[0]) / M;

	for (i = 0; i < NN; i++)
	{
		x[i] = (beta2 * x[i - 1]) % M;
		c[i] = ((double)x[i]) / M;
	}


	//Sample generation by the Maclaurin-Marsaglia method
	double* a = new double[n];

	foutMM << "Makl-Mars:\n";
	for (i = 0; i < n; i++)
	{
		a[i] = c[((long)(b[i] * n)) + n * i];
		foutMM << a[i] << "\n";
	}

	std::cout << "\n\nMcLaren-Marsali sensor\n";
	std::cout << "**********************************\n";
	KolmogorovTest(a, n);
	PirsonTest(a, n, 10);
	std::cout << "**********************************\n";


	int m;
	std::cin >> m;

	delete[] b;
	delete[] c;
	delete[] x;

	foutMC.close();
	foutMM.close();

	return 1;
}
