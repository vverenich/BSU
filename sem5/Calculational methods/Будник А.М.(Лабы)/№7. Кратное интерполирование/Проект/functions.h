#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
}

template <typename T>
T fdif (T x)
{
	return 0.8 * exp(x) - 0.2 * sin(x);
}

template <typename T>
T Ermit (T pt, int n, T* x, T** rr)
{
	T res = 0, add;
	for (int i = 0; i <= n; ++i)
	{
		add = rr[0][i];
		for (int j = 0; j < i; ++j)
			add *= (pt - x[j]);
		res += add;
	}
	return res;
}

template <typename T>
void createNodes (int n, T* x, T* fx, T* fdifx, T xf, T xl)
{
	for (int i = 0; i < n; i += 2)
	{
		x[i] = x[i+1] = xf + (xl - xf) * i / (n - 1);
		fx[i] = fx[i+1] = f(x[i]);
		fdifx[i] = fdifx[i+1] = fdif(x[i]);
	}
}

template <typename T>
void createMatrix (int n, T** rr, T* x, T* fx, T* fdif)
{
	for (int i = 0; i <= n; ++i)
		rr[i][0] = fx[i];
	for (int i = 0; i < n; ++i)
		rr[i][1] = (x[i] == x[i+1] ? fdif[i] : (rr[i+1][0] - rr[i][0]) / (x[i+1] - x[i]));
	for (int j = 2; j <= n; ++j)
		for (int i = 0; i <= n - j; ++i)
			rr[i][j] = (rr[i+1][j-1] - rr[i][j-1]) / (x[i+j] - x[i]);
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
T findTheoreticalResidual (T pt, int n, T* x, T** rr)
{
	T mul = 1;
	for (int i = 0; i <= n; ++i)
		mul *= (pt - x[i]) / (i + 1);
	switch (n % 4)
	{
	case 0:
		return mul * (0.8 * exp(3.0) - 0.2 * sin(3.0));
	case 1:
		return mul * (0.8 * exp(3.0) - 0.2 * cos(3.0));
	case 2:
		return mul * (0.8 * exp(3.0) + 0.2 * sin(3.0));
	case 3:
		return mul * (0.8 * exp(3.0) + 0.2 * cos(3.0));
	}
}

template <typename T>
void printRRmatrix (T** rr, int n, std::ostream& os, int width)
{
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= n-i; ++j)
			os << setw(width) << rr[i][j];
		os << "\n";
	}
}

#endif