#define _USE_MATH_DEFINES
#include <omp.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;

class Timer
{
private:
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, std::ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

class Program
{
public:
	static void Main()
	{
		int n = 0;
		cout << "Enter the number of split points\n";
		cin >> n;
		if (cin.fail() || n < 1) {
			cout << "uncorrect n-value\n";
			return;
		}

		double integralOMP = integral(f, 0, M_PI / 4, n);
		double integralReal = sin(M_PI / 4);
		cout << "\nIntegral:\n";
		cout << "\t- openMP:\t" << integralOMP << "\n";
		cout << "\t- Real:\t\t" << integralReal << "\n";
	}

private:
	static double f(double x)
	{
		return cos(x);
	}

	static double integral(double func(double x), double A, double B, long long N)
	{
		Timer t;
		double sum = 0;
		double step = (B - A) / N;
        #pragma omp parallel for reduction(+:sum)
		for (int i = 1; i < N; ++i) {
			//cout << "Thread ID for N points: " << omp_get_thread_num() << "\n";
			sum += func(A + i * step);
		}
		sum = step * (sum + (f(A) + f(B)) / 2);
		cout << "\nTime: " << t.elapsed();
		return sum;
	}
};

int main()
{
	Program::Main();
	system("pause");
}