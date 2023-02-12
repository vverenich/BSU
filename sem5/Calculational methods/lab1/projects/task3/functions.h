#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

#define M_PI 3.1415926535897932384626433832795

double f (double x)
{
    return 0.3 * std::exp(-x) + 0.7 * std::cos(x);
}

double P (double x, int n, double* xn, double* fxn)
{
    double res = 0;
    double num = 1, denom;
    for (int i = 0; i <= n; ++i)
    {
        if (x == xn[i])
            return fxn[i];
        num *= (x - xn[i]);
    }
    for (int i = 0; i <= n; ++i)
    {
        denom = 1;
        for (int j = 0; j < i; ++j)
            denom *= (xn[i] - xn[j]);
        for (int j = i + 1; j <= n; ++j)
            denom *= (xn[i] - xn[j]);
        res += fxn[i] * num / (x - xn[i]) / denom;
    }
    return res;
}

void createNodes (int n, double* x, double* fx, double a, double b)
{
    double add = (a + b) / 2, mul = (b - a) / 2;
    for (int i = 0; i <= n; ++i)
    {
        x[i] = add + mul * std::cos (M_PI * (2 * (n - i) + 1) / 2 / (n + 1));
        fx[i] = f (x[i]);
    }
}

double findRealResidual (double x, double px)
{
    return f(x) - px;
}

double findTheoreticalResidual (int n, double a, double b)
{
    double mul = (b - a) / 2;
    for (int i = 1; i <= n; ++i)
        mul *= ((b - a) / (i + 1) / 4);
    switch (n % 4)
    {
    case 0:
        return (0.3 * std::exp(-1.3) - 0.7 * std::sin(1.3)) * mul;
    case 1:
        return (0.3 * std::exp(-1.3) - 0.7 * std::cos(1.3)) * mul;
    case 2:
        return (0.3 * std::exp(-1.3) + 0.7 * std::sin(1.3)) * mul;
    case 3:
        return (0.3 * std::exp(-1.3) + 0.7 * std::cos(1.3)) * mul;
    }
}

#endif
