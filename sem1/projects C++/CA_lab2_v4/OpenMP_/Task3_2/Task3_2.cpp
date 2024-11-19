#include <omp.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

class Program
{
public:
	static void Main()
	{
		omp_set_num_threads(128);
		cout << integral(h, 0, 15, 100000) << endl;
	}

private:
	static double h(double x)
	{
		return (x * x + 6 * x + 4);
	}

	static int integral(double func(double x), double A, double B, long long N)
	{
		double summ = 0;
		double step = (B - A) / N;
		auto startTime = omp_get_wtime();
		#pragma omp parallel for reduction(+:summ)
		for (int i = 0; i < N; ++i)
		{
			double a = A + i * step;
			double b = a + step;
			double a_b = (a + b) / 2;
			#pragma omp critical
			{
				summ += (b - a) * (func(a) + 4 * func(a_b) + func(b)) / 6;
			}
		}

		return (int)GetEllapsedMilliseconds(startTime);
	}

	static double GetEllapsedMilliseconds(double startTime)
	{
		return (omp_get_wtime() - startTime) * 1000;
	}
};

int main()
{
	Program::Main();
	system("pause");
}