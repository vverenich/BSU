#include <omp.h>
#include <iostream>
#include <chrono>

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

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
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

const double PI = 3.141592653589793238463;

void getMessageAboutWrongInput() {
	std::cout << "\nPlease enter a valid number!\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double functionF(double x, const double a, const double b) {
	if (x >= a && x <= 1) {
		return 2 * x - 2;
	} else if (x > 1 && x <= b) {
		return sin(x - 1);
	}
	return -1;
}

void calculateIntegralSimpson(int64_t N, double a) {
	omp_set_num_threads(10);
	double resultForN{ 0 };
	double resultFor4N{ 0 };
	double b{ 1 + PI / 2 };
	double hN{ (b - a) / N };
	double h4N{ (b - a) / (4 * N) };
	//std::cout << h << " " << b << "\n";
#pragma omp parallel sections
	{
#pragma omp section
		{
#pragma omp parallel for schedule(static,1) ordered
			for (int i{ 0 }; i < N + 1; ++i) {
				if (i != 0 && i != N - 1) {
					if (i % 2 == 1) {
						resultForN += (hN / 3) * functionF(a + i * hN, a, b) * 4;
					} else {
						resultForN += (hN / 3) * functionF(a + i * hN, a, b) * 2;
					}
				} else {
					resultForN += (hN / 3) * functionF(a + i * hN, a, b);
				}
			}
		}
#pragma omp section 
		{
#pragma omp parallel for schedule(static,1) ordered
			for (int i{ 0 }; i < 4 * N + 1; ++i) {
				if (i != 0 && i != 4 * N - 1) {
					if (i % 2 == 1) {
						resultFor4N += (h4N / 3) * functionF(a + i * h4N, a, b) * 4;
					} else {
						resultFor4N += (h4N / 3) * functionF(a + i * h4N, a, b) * 2;
					}
				} else {
					resultFor4N += (h4N / 3) * functionF(a + i * h4N, a, b);
				}
			}
		}
	}
	std::cout << "\nIntegral, calculated using Simpson's method (N), equals to " << resultForN;
	std::cout << "\nIntegral, calculated using Simpson's method (4*N), equals to " << resultFor4N;
}

double calculateIntegral(double a) {
	auto lambda1{ [](double x) { //indefinite integral of f1(x) = 2*x-2
		return x * x - 2 * x;
	} };

	auto lambda2{ [](double x) {//indefinite integral of f2(x) = sin(x-1)
		return -cos(x - 1);
	} };

	return lambda1(1) - lambda1(a) + lambda2(1 + PI / 2) - lambda2(1);
}

int main() {
	int64_t N;
	for (;;) {
		std::cout << "Please enter N: ";
		if (std::cin >> N && N > 0) {
			break;
		} else {
			getMessageAboutWrongInput();
		}
	}

	double a;
	for (;;) {
		std::cout << "Please enter a: ";
		if (std::cin >> a && a < 1) {
			break;
		} else {
			getMessageAboutWrongInput();
		}
	}

	Timer timer;
	double result;
	calculateIntegralSimpson(N, a);

	std::cout << "\nIntegral, calculated using RTL, equals to " << calculateIntegral(a);
	std::cout << "\nElapsed: " << timer.elapsed() << " s";
}