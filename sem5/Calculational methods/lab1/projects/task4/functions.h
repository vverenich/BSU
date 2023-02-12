#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

void SED (double** m, double* v, int num);
void SEDInvert (double** m, double* v, double* x, int num);

double f (double x)
{
    return 0.3 * exp(-x) + 0.7 * cos(x);
}

double pow (double base, int degree)
{
    double res = 1;
    for (int i = 0; i < degree; ++i)
        res *= base;
    return res;
}

void FindCoefficients (int n, double** A, double* b, double* coef)
{
    SED (A, b, n+1);
    SEDInvert (A, b, coef, n+1);
}

double Polynom (double pt, int n, double* coef)
{
    double res = 0;
    for (int i = 0; i <= n; ++i)
        res += coef[i] * pow (pt, i);
    return res;
}

void createNodes (int N, double* x, double* fx, double xf, double xl, double& h)
{
    h = (xl - xf) / (N - 1);
    x[0] = xf;
    fx[0] = f(x[0]);
    for (int i = 1; i < N; ++i)
    {
        x[i] = x[i-1] + h;
        fx[i] = f(x[i]);
    }
}

void createMatrix (int n, int N, double* x, double** A, double* b, double* fx)
{
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            A[i][j] = 0;
            for (int p = 0; p < N; ++p)
                A[i][j] += pow (x[p], i + j);
        }
        b[i] = 0;
        for (int j = 0; j < N; ++j)
            b[i] += fx[j] * pow (x[j], i);
    }
}

double findRealResidual (double x, double px)
{
    return f(x) - px;
}

void SEDStep (double** m, double* v, int num, int step)
{
    double leadEl = m[step][step];
    m[step][step] = 1;
    for (int j = step + 1; j < num; ++j)
        m[step][j] /= leadEl;
    v[step] /= leadEl;
    for (int i = step + 1; i < num; ++i)
    {
        double firstEl = m[i][step];
        m[i][step] = 0;
        for (int j = step + 1; j < num; ++j)
            m[i][j] -= ( firstEl * m[step][j] );
        v[i] -= ( firstEl * v[step] );
    }
}

void SED (double** m, double* v, int num)
{
    for (int i = 0; i < num; ++i)
        SEDStep (m, v, num, i);
}

void SEDInvert (double** m, double* v, double* x, int num)
{
    for (int i = num - 1; i >= 0; --i)
    {
        double sumToSub = 0;
        for (int j = i + 1; j < num; ++j)
            sumToSub += ( m[i][j] * x[j] );
        x[i] = v[i] - sumToSub;
    }
}

#endif
