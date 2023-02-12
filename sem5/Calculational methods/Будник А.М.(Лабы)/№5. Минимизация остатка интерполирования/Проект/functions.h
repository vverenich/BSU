#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define M_PI 3.1415926535897932384626433832795

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
}

template <typename T>
T P (T x, int n, T* xn, T* fxn)
{
	T res = 0;
	T num = 1, denom;
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

template <typename T>
void createNodes (int n, T* x, T* fx, T a, T b)
{
	T add = (a + b) / 2, mul = (b - a) / 2;
	for (int i = 0; i <= n; ++i)
	{
		x[i] = add + mul * cos (M_PI * (2 * (n - i) + 1) / 2 / (n + 1));
		fx[i] = f (x[i]);
	}
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
T findTheoreticalResidual (int n, T a, T b)
{
	T mul = (b - a) / 2;
	for (int i = 1; i <= n; ++i)
		mul *= ((b - a) / (i + 1) / 4);
	switch (n % 4)
	{
	case 0:
		return (0.8 * exp(3.0) - 0.2 * sin(3.0)) * mul;
	case 1:
		return (0.8 * exp(3.0) - 0.2 * cos(3.0)) * mul;
	case 2:
		return (0.8 * exp(3.0) + 0.2 * sin(3.0)) * mul;
	case 3:
		return (0.8 * exp(3.0) + 0.2 * cos(3.0)) * mul;
	}
}

#endif