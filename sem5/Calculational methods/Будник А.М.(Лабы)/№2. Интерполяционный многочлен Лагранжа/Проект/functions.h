#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
void createNodes (int n, T* x, T* fx, T xf, T xl, T& h)
{
	h = (xl - xf) / n;
	x[0] = xf;
	fx[0] = f(x[0]);
	for (int i = 1; i <= n; ++i)
	{
		x[i] = x[i-1] + h;
		fx[i] = f(x[i]);
	}
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
T findTheoreticalResidual (T x, int n, T* xn)
{
	T w = x - xn[0];
	for (int i = 1; i <= n; ++i)
	{
		w *= (x - xn[i]);
		w /= i;
	}
	w = abs(w);
	switch (n%4)
	{
	case 0:
		return (0.8 * exp(3.0) - 0.2 * sin(3.0)) * w;
	case 1:
		return (0.8 * exp(3.0) - 0.2 * cos(3.0)) * w;
	case 2:
		return (0.8 * exp(3.0) + 0.2 * sin(3.0)) * w;
	case 3:
		return (0.8 * exp(3.0) + 0.2 * cos(3.0)) * w;
	}
}

#endif