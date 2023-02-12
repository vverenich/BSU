#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <iostream>

const int realN{60000};
const int minimalForTheoreticalResidualN{37};

double f (double x)
{
    return 0.3 * exp(-x) + 0.7 * cos(x);
}

double integralF (double x)
{
    return -0.3 * exp(-x) + 0.7 * sin(x);
}

double ExactIntegral (double a, double b)
{
    return integralF(b) - integralF(a);
}

double legendrePolynomialFirstDerivative(double x)
{
    return (5.0 / 2.0) * x * (7 * std::pow(x, 2) -  3.0);
}

double getCoefficient(double x)
{
    return 2.0 / ((1 - pow(x, 2)) * pow(legendrePolynomialFirstDerivative(x), 2));
}

double IntegralGauss (double a, double b, const int n = 4)
{
    double	*t = new double [n],
            *A = new double [n];
    t[0] = - sqrt(3.0 / 7 - (2 * sqrt(6.0 / 5) / 7));
    t[1] = sqrt(3.0 / 7 - (2 * sqrt(6.0 / 5) / 7));
    t[2] = - sqrt(3.0 / 7 + (2 * sqrt(6.0 / 5) / 7));
    t[3] = sqrt(3.0 / 7 + (2 * sqrt(6.0 / 5) / 7));

    A[0] = getCoefficient(t[0]);
    A[1] = getCoefficient(t[1]);
    A[2] = getCoefficient(t[2]);
    A[3] = getCoefficient(t[3]);

    std::cout << "Coefficients: \n";
    std::cout << A[0] << "\n";
    std::cout << A[1] << "\n";
    std::cout << A[2] << "\n";
    std::cout << A[3] << "\n";

    double integral = 0;
    for (int i = 0; i < n; ++i) {
        integral += A[i] * f ((a + b + (b - a) * t[i]) / 2);
    }

    delete [] A;
    delete [] t;

    return integral * (b - a) / 2;
}

double FindResidual (double a, double b, double integral)
{
    return ExactIntegral (a, b) - integral;
}

double getMaxDerivativeOnInterval()
{
    return 0.891;
}

double getTheoreticalDifferenceByGauss(size_t n, double a, double b)
{
    double remainder = getMaxDerivativeOnInterval();

    remainder *= pow(((b-a)/2), 2 * n + 3);
    remainder *= pow(2, 2*n + 3);
    remainder /= (2*n + 3);

    for(size_t i{1}; i < n + 1; ++i)
    {
        remainder *= pow(i, 4);
    }

    for(size_t i{1}; i < 2*n + 2; ++i)
    {
        remainder /= pow(i, 3);
    }

    return remainder;

}

// This value has been found by me in report
int getN()
{
    return 62;
}

double getH(const double a, const double b, const double N)
{
    return (b - a) / N;
}

double trapezoid( double a, double b)
{
    double result = (f(a) + f(b)) / 2;
    double h = getH(a, b, realN);
    size_t N = realN;

    for (size_t i{1}; i < N - 1; ++i) {
        result += (f(a + h * i));
    }

    return result * h;
}

double getAbsMaxSecondDerivative()
{
    return 0.4466;
}

double getTheoreticalDifferenceByTrapezoid(double a, double b)
{
    return -pow((b - a), 3) * getAbsMaxSecondDerivative() / 12 / pow(minimalForTheoreticalResidualN, 2);
}


#endif
