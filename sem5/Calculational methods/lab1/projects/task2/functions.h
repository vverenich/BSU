#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <fstream>
#include <iomanip>

double f (double x)
{
    return 0.3 * std::exp(-x) + 0.7 * std::cos(x);
}

double beginning (double x, int n, double** kr, double xf, double h)
{
    double t = (x - xf) / h;
    double res = kr[0][0];
    double mul = t;
    for (int i = 1; i <= n; ++i) {
        res += (kr[0][i] * mul);
        mul *= ((t - i) / (i + 1));
    }

    return res;
}

double NewtonStirling (double x, int n, double** kr, double* xn, double h)
{
    int midindex = n / 2;
    double t = (x - xn[midindex]) / h;
    double res = kr[midindex][0];
    double mul = t;
    for (int i = 1; i <= midindex; ++i) {
        res += (kr[midindex-i][2*i-1] * mul);
        mul *= ((t + i) / (2 * i));
        res += (kr[midindex-i][2*i] * mul);
        mul *= ((t - i) / (2 * i + 1));
    }

    return res;
}

double NewtonBessel (double x, int n, double** kr, double* xn, double h)
{
    int midindex = n / 2;
    double t = (x - xn[midindex]) / h;
    double res = 0;
    double mul = 1;
    for (int i = 0; i <= midindex; ++i) {
        res += (kr[midindex-i][2*i] * mul);
        mul *= ((t + i) / (2 * i + 1));
        res += (kr[midindex-i][2*i+1] * mul);
        mul *= ((t - i - 1) / (2 * i + 2));
    }

    return res;
}

double center (double x, int n, double** kr, double* xn, double h)
{
    if ((n & 1) == 0) {
        return NewtonStirling (x, n, kr, xn, h);
    } else {
        return NewtonBessel (x, n, kr, xn, h);
    }
}

double ending (double x, int n, double** kr, double xl, double h)
{
    double t = (x - xl) / h;
    double res = kr[n][0];
    double mul = t;
    for (int i = 1; i <= n; ++i)
    {
        res += (kr[n-i][i] * mul);
        mul *= ((t + i) / (i + 1));
    }

    return res;
}

void createNodes (int n, double* x, double* fx, double xf, double xl, double& h)
{
    h = (xl - xf) / n;
    x[0] = xf;
    fx[0] = f(x[0]);
    for (int i = 1; i <= n; ++i) {
        x[i] = x[i-1] + h;
        fx[i] = f(x[i]);
    }
}

void createMatrix (int n, double** kr, double* fx)
{
    for (int i = 0; i <= n; ++i) {
        kr[i][0] = fx[i];
    }

    for (int j = 1; j <= n; ++j) {
        for (int i = 0; i <= n - j; ++i) {
            kr[i][j] = (kr[i+1][j-1] - kr[i][j-1]);
        }
    }
}

double findRealResidual (double x, double px)
{
    return f(x) - px;
}

double getMaxFourthDerivativeInRangeFromAtoB()
{
    return f(0.3);
}

double findTheoreticalResidual (int n, double* xArr, double x)
{
    double result = 1;
    for (int i = 0; i < n; ++i) {
        result *= (x - xArr[i]);

        if (i > 0) {
           result /= i;
        }
    }

    return result * getMaxFourthDerivativeInRangeFromAtoB();
}

void printKRmatrix (double** rr, int n, std::ostream& os, int width)
{
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n-i; ++j) {
            os << std::setw(width) << rr[i][j] << "\t";
        }

        os << "\n";
    }
}

#endif
