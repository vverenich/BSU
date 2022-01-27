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

double functionF(const double x) {
	if (x >= -PI / 2 && x <= PI / 2) {
		return sin(x) - x;
	}
	return -1;
}

void getMaxSecondDerivative(const int64_t N, double &result) {
	omp_set_num_threads(5);

	double a{ -PI / 2 };
	double b = { PI / 2 };
	double h = { (b - a) / N };
	result = 0;

#pragma omp parallel for schedule(static,1) ordered
	for (int i{ 1 }; i < N; ++i) {
		double f = (functionF(a + h * (i - 1)) - 2 * functionF(a + h * i) + functionF(a + h * (i + 1))) / (h * h);

		if (std::abs(f) > result) {
			result = std::abs(f);
		}
	}
}

double getCalculatedMaxSecondDerivative() {
	return 1;
}

int main() {
	int64_t N;
	for (;;) {
		std::cout << "Please enter N: ";
		if (std::cin >> N && N > 1) {
			break;
		} else {
			getMessageAboutWrongInput();
		}
	}
	
	Timer timer;
	double result;
	getMaxSecondDerivative(N, result);

	std::cout << "\nAbsolute max value of second derivative, calculated using several threads, equals to " << result;
	std::cout << "\nReal absolute max value of second derivative equals to " << getCalculatedMaxSecondDerivative();
	std::cout << "\nElapsed: " << timer.elapsed() << " s";
}