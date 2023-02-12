#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T Lagrange (T x, int n, T* xn, T* fxn)
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
void SED (T** m, T* v, int num)
{
	for (int step = 0; step < num; ++step)
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

template <typename T>
T f (T x)
{
	return 1 + exp(x);
}

template <typename T>
T K (T x, T s)
{
	return 1 / log (9 + x * s);
}

template <typename T>
T Quadrature (T pt, T a, T b, T l, int n, T* y)
{
	T h = (b - a) / n;
	T* x = new T [n+1];
	x[0] = a;
	for (int i = 1; i <= n; ++i)
		x[i] = x[i-1] + h;
	T* f_ = new T [n+1];
	for (int i = 0; i <= n; ++i)
		f_[i] = f(x[i]);
	T** A = new T* [n+1];
	for (int i = 0; i <= n; ++i)
		A[i] = new T [n+1];
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= n; ++j)
			A[i][j] = - l * h * K (x[i], x[j]);
		A[i][0] /= 2;
		A[i][n] /= 2;
		++A[i][i];
	}
	SED (A, f_, n + 1);
	SEDInvert (A, f_, y, n + 1);
	T res = Lagrange (pt, n, x, y);
	for (int i = 0; i <= n; ++i)
		delete [] A[i];
	delete [] A;
	delete [] f_;
	delete [] x;
	return res;
}

template <typename T>
T Approximation (T pt, int M, T a, T b, T l, int n, T* y)
{
	T h = (b - a) / n;
	T* x = new T [n+1];
	x[0] = a;
	for (int i = 1; i <= n; ++i)
		x[i] = x[i-1] + h;
	T	*yPrev = new T [n+1],
		*yCurr = new T [n+1];
	for (int i = 0; i <= n; ++i)
		y[i] = yPrev[i] = f(x[i]);
	T powl = l;
	for (int i = 1; i <= M; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			yCurr[j] = (K (x[j], x[0]) * yPrev[0] + K (x[j], x[n]) * yPrev[n]) / 2;
			for (int k = 1; k < n; ++k)
				yCurr[j] += K (x[j], x[k]) * yPrev[k];
			yCurr[j] *= h;
		}
		for (int j = 0; j <= n; ++j)
		{
			yPrev[j] = yCurr[j];
			y[j] += powl * yCurr[j];
		}
		powl *= l;
	}
	T res = Lagrange (pt, n, x, y);
	delete [] yCurr;
	delete [] yPrev;
	delete [] x;
	return res;
}

#endif