#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
}

template <typename T>
T pow (T base, int degree)
{
	T res = 1;
	for (int i = 0; i < degree; ++i)
		res *= base;
	return res;
}

template <typename T>
void FindCoefficients (int n, T** A, T* b, T* coef)
{
	SED (A, b, n+1);
	SEDInvert (A, b, coef, n+1);
}

template <typename T>
T Polynom (T pt, int n, T* coef)
{
	T res = 0;
	for (int i = 0; i <= n; ++i)
		res += coef[i] * pow (pt, i);
	return res;
}

template <typename T>
void createNodes (int N, T* x, T* fx, T xf, T xl, T& h)
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

template <typename T>
void createMatrix (int n, int N, T* x, T** A, T* b, T* fx)
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

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
void SEDStep (T** m, T* v, int num, int step)
{
	T leadEl = m[step][step];
	m[step][step] = 1;
	for (int j = step + 1; j < num; ++j)
		m[step][j] /= leadEl;
	v[step] /= leadEl;
	for (int i = step + 1; i < num; ++i)
	{
		T firstEl = m[i][step];
		m[i][step] = 0;
		for (int j = step + 1; j < num; ++j)
			m[i][j] -= ( firstEl * m[step][j] );
		v[i] -= ( firstEl * v[step] );
	}
}

template <typename T>
void SED (T** m, T* v, int num)
{
	for (int i = 0; i < num; ++i)
		SEDStep (m, v, num, i);
}

template <typename T>
void SEDInvert (T** m, T* v, T* x, int num)
{
	for (int i = num - 1; i >= 0; --i)
	{
		T sumToSub = 0;
		for (int j = i + 1; j < num; ++j)
			sumToSub += ( m[i][j] * x[j] );
		x[i] = v[i] - sumToSub;
	}
}

#endif