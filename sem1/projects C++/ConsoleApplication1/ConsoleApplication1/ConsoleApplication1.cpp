#define _USE_MATH_DEFINES

#include <omp.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <utility>

using namespace std;
const int ThreadsCount = 8;

class Program
{
public:
    static void Main()
    {
        omp_set_num_threads(2);
        double a = 0;
        double b = 3;
        int n = 0;
        cout << "Enter count of ortrezkov:\n";
        cin >> n;

        cout << "Max in case 4N: " << findMax(a, b, n, f) << "\n";
        cout << "Real value: " << 6 - M_PI;

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

    static double findMax(double a, double b, int n, double f(double x))
    {
        double maxValueFirst = INT_MIN;


        const int N2 = 4 * n;
        double stepFirst = (M_PI / 2 - a) / N2 / 2;
        double stepSecond = (b - M_PI / 2) / N2 / 2;
        double maxValue = INT_MIN;
        auto startTime = omp_get_wtime();
#pragma omp parallel sections
        {
#pragma omp section
            {
#pragma omp parallel for num_threads(ThreadsCount)
                for (int i = 0; i < N2 / 2; i++)
                {
                    double derivativeK = (f(a + i * stepFirst + stepFirst) -
                        f(a + i * stepFirst)) / stepFirst;


                    if (fabs(derivativeK) > maxValue) {
#pragma omp critical
                        {
                            if (fabs(derivativeK) > maxValue) {
                                maxValue = fabs(derivativeK);
                            }
                        }
                    }
                }
            }

#pragma omp section
            {
#pragma omp parallel for num_threads(ThreadsCount)
                for (int i = 0; i < N2 / 2; i++)
                {
                    double derivativeK = (f(M_PI / 2 + i * stepSecond + stepSecond) -
                        f(M_PI / 2 + i * stepSecond)) / stepSecond;


                    if (fabs(derivativeK) > maxValue) {
#pragma omp critical
                        {
                            if (fabs(derivativeK) > maxValue) {
                                maxValue = fabs(derivativeK);
                            }
                        }
                    }
                }
            }
        }
        cout << (int)GetEllapsedMilliseconds(startTime) << "\n";
        return maxValue;
    }

    static double GetEllapsedMilliseconds(double startTime)
    {
        return (omp_get_wtime() - startTime) * 1000;
    }
};

int main() {
    Program::Main();
}