#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
}

template <typename T>
T beginning (T x, int n, T** kr, T xf, T h)
{
	T t = (x - xf) / h;
	T res = kr[0][0];
	T mul = t;
	for (int i = 1; i <= n; ++i)
	{
		res += (kr[0][i] * mul);
		mul *= ((t - i) / (i + 1));
	}
	return res;
}

template <typename T>
T center (T x, int n, T** kr, T* xn, T h)
{
	if ((n & 1) == 0)
		return NewtonStirling (x, n, kr, xn, h);
	else
		return NewtonBessel (x, n, kr, xn, h);
}

template <typename T>
T NewtonStirling (T x, int n, T** kr, T* xn, T h)
{
	int midindex = n / 2;
	T t = (x - xn[midindex]) / h;
	T res = kr[midindex][0];
	T mul = t;
	for (int i = 1; i <= midindex; ++i)
	{
		res += (kr[midindex-i][2*i-1] * mul);
		mul *= ((t + i) / (2 * i));
		res += (kr[midindex-i][2*i] * mul);
		mul *= ((t - i) / (2 * i + 1));
	}
	return res;
}

template <typename T>
T NewtonBessel (T x, int n, T** kr, T* xn, T h)
{
	int midindex = n / 2;
	T t = (x - xn[midindex]) / h;
	T res = 0;
	T mul = 1;
	for (int i = 0; i <= midindex; ++i)
	{
		res += (kr[midindex-i][2*i] * mul);
		mul *= ((t + i) / (2 * i + 1));
		res += (kr[midindex-i][2*i+1] * mul);
		mul *= ((t - i - 1) / (2 * i + 2));
	}
	return res;
}

template <typename T>
T ending (T x, int n, T** kr, T xl, T h)
{
	T t = (x - xl) / h;
	T res = kr[n][0];
	T mul = t;
	for (int i = 1; i <= n; ++i)
	{
		res += (kr[n-i][i] * mul);
		mul *= ((t + i) / (i + 1));
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
void createMatrix (int n, T** kr, T* fx)
{
	for (int i = 0; i <= n; ++i)
		kr[i][0] = fx[i];
	for (int j = 1; j <= n; ++j)
		for (int i = 0; i <= n - j; ++i)
			kr[i][j] = (kr[i+1][j-1] - kr[i][j-1]);
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
void printKRmatrix (T** rr, int n, std::ostream& os, int width)
{
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= n-i; ++j)
			os << setw(width) << rr[i][j];
		os << "\n";
	}
}

#endif