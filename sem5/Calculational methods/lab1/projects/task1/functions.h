#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <fstream>
#include <iomanip>

double f (double x)
{
    return 0.3 * std::exp(-x) + 0.7 * std::cos(x);
}

double lagrangePolynomial (double x, int n, double* xn, double* fxn)
{
    double result = 0;
    double numerator = 1;
    double denominator;

    for (int i = 0; i <= n; ++i) {
        if (x == xn[i]) {
            return fxn[i];
        }

        numerator *= (x - xn[i]);
    }

    for (int i = 0; i <= n; ++i) {
        denominator = 1;
        for (int j = 0; j < i; ++j) {
            denominator *= (xn[i] - xn[j]);
        }

        for (int j = i + 1; j <= n; ++j) {
            denominator *= (xn[i] - xn[j]);
        }

        result += fxn[i] * numerator / (x - xn[i]) / denominator;
    }

    return result;
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

double getRealResidual (double x, double px)
{
    return std::abs(f(x) - px);
}

double getTheoreticalResidualNewton (double x, int n, double* xn, double** rrn)
{
    rrn[n+1][0] = f(x);
    for (int i = 1; i <= n+1; ++i) {
        rrn[n-i+1][i] = (rrn[n-i+2][i-1] - rrn[n-i+1][i-1]) / (x - xn[n-i+1]);
    }

    double w = x - xn[0];
    for (int i = 1; i <= n; ++i) {
        w *= (x - xn[i]);
    }

    return std::abs(w * rrn[0][n+1]);
}

void createMatrix (int n, double** rr, double* x, double* fx)
{
    for (int i = 0; i <= n; ++i) {
        rr[i][0] = fx[i];
    }

    for (int j = 1; j <= n; ++j) {
        for (int i = 0; i <= n - j; ++i) {
            rr[i][j] = (rr[i+1][j-1] - rr[i][j-1]) / (x[i+j] - x[i]);
        }
    }
}

void printRRmatrix (double** rr, int n, std::ostream& os, int width)
{
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n-i; ++j) {
            os << std::setw(width) << rr[i][j];
        }

        os << "\n";
    }
}


#endif
