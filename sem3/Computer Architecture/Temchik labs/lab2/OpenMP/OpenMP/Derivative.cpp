#define _USE_MATH_DEFINES

#include <omp.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <utility>
#include <chrono>

using namespace std;

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

class Program
{
public:
    static void Main()
    {

        omp_set_nested(true);
        double a = 0;
        double b = 3;
        int n = 0;
        cout << "Enter the number of split points\n";
        cin >> n;
        if (cin.fail() || n < 1) {
            cout << "uncorrect n-value\n";
            return;
        }

        pair<double, double> pParallel = findMaxParallel(a, b, n, f);
        cout << "Max value of |f'(x)|:\n";

        cout << "\t- In case N1 = N:\t" << pParallel.first << "\n";
        cout << "\t- In case N2 = 4N:\t" << pParallel.second << "\n";
        cout << "\t- Real:\t\t\t" << 6 - M_PI << "\n";
    }

private:
    static double f(double x)
    {
        if (x < M_PI / 2) {
            return sin(x);
        }
        else {
            return (x - M_PI / 2) * (x - M_PI / 2) + 1;
        }

    }

    static pair<double, double> findMaxParallel(double a, double b, int n, double f(double x))
    {
        double stepFirst = (b - a) / n;
        double maxValueFirst = INT_MIN;

        double stepSecond = (b - a) / 4 / n;
        double maxValueSecond = INT_MIN;

        Timer t;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                #pragma omp parallel for schedule(static)
                for (int i = 0; i <= n; i++)
                {
                    //cout << "Thread ID for N points: " << omp_get_thread_num() << "\n";
                    double derivativeK = (f(a + i * stepFirst + stepFirst) -
                        f(a + i * stepFirst)) / stepFirst;


                    if (fabs(derivativeK) > maxValueFirst) {
                        #pragma omp critical
                        {
                            maxValueFirst = max(fabs(derivativeK), maxValueFirst);
                        }
                    }
                }
            }

            #pragma omp section
            {
                #pragma omp parallel for schedule(static)
                for (int i = 0; i <= 4 * n; i++)
                {
                    //cout << "Thread ID for 4N points: " << omp_get_thread_num() << "\n";
                    double derivativeK = (f(a + i * stepSecond + stepSecond) -
                        f(a + i * stepSecond)) / stepSecond;


                    if (fabs(derivativeK) > maxValueSecond) {
                        #pragma omp critical
                        {
                            maxValueSecond = max(fabs(derivativeK), maxValueSecond);
                        }
                    }
                }
            }
        }
        cout << "\nTime: " << t.elapsed() << "\n\n";
        return make_pair(maxValueFirst, maxValueSecond);
    }
};

int main() {
    Program::Main();

    return 0;
}
