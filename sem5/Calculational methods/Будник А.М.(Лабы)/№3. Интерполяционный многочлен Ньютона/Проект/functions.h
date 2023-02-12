#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
}

template <typename T>
T P (T x, int n, T* xn, T** rrn)
{
	T res = 0, add;
	for (int i = 0; i < n; ++i)
	{
		add = rrn[0][i];
		for (int j = 0; j < i; ++j)
			add *= (x - xn[j]);
		res += add;
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
void createMatrix (int n, T** rr, T* x, T* fx)
{
	for (int i = 0; i <= n; ++i)
		rr[i][0] = fx[i];
	for (int j = 1; j <= n; ++j)
		for (int i = 0; i <= n - j; ++i)
			rr[i][j] = (rr[i+1][j-1] - rr[i][j-1]) / (x[i+j] - x[i]);
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

template <typename T>
T findTheoreticalResidual (T x, int n, T* xn, T** rrn)
{
	rrn[n+1][0] = f(x);
	for (int i = 1; i <= n+1; ++i)
		rrn[n-i+1][i] = (rrn[n-i+2][i-1] - rrn[n-i+1][i-1]) / (x - xn[n-i+1]);
	T w = x - xn[0];
	for (int i = 1; i <= n; ++i)
		w *= (x - xn[i]);
	return abs(w * rrn[0][n+1]);
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