#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 0.8 * exp(x) + 0.2 * cos(x);
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
void createMatrix (int n, T h, T* fx, T** A, T* b)
{
	for (int i = 0; i < n - 1; ++i)
	{
		if (i > 0)
			A[i][i-1] = h / 6;
		A[i][i] = h * 2 / 3;
		if (i < n - 2)
			A[i][i+1] = h / 6;
		b[i] = (fx[i+2] + fx[i] - 2 * fx[i+1]) / h;
	}
}

template <typename T>
void findLinCoefs (T** m, T* v, int num, T* alpha, T* beta)	//	|alpha| = num-1;	|beta| = num;
{
	int numf = num-1;
	alpha[0] = - m[0][1] / m[0][0];
	beta[0] = v[0] / m[0][0];
	T tmp;
	for (int i = 1; i < numf; ++i)
	{
		tmp = m[i][i] + alpha[i-1] * m[i][i-1];
		alpha[i] = - m[i][i+1] / tmp;
		beta[i] = (v[i] - beta[i-1] * m[i][i-1]) / tmp;
	}
	tmp = m[numf][numf] + alpha[numf-1] * m[numf][numf-1];
	beta[numf] = (v[numf] - beta[numf-1] * m[numf][numf-1]) / tmp;
}

template <typename T>
void findUnknown (T* x, int num, T* alpha, T* beta)
{
	int numf = num-1;
	x[numf] = beta[numf];
	for (int i = numf - 1; i >= 0; --i)
		x[i] = alpha[i] * x[i+1] + beta[i];
}

template <typename T>
void splineCubeVector (int n, T h, T* fxn, T* M)
{
	T** A = new T* [n-1];
	for (int i = 0; i < n - 1; ++i)
		A[i] = new T [n-1];
	T* b = new T [n-1];
	createMatrix (n, h, fxn, A, b);
	T* alpha = new T [n-2];
	T* beta = new T [n-1];
	findLinCoefs (A, b, n-1, alpha, beta);
	findUnknown (M, n-1, alpha, beta);
	delete [] beta;
	delete [] alpha;
	delete [] b;
	for (int i = 0; i < n - 1; ++i)
		delete [] A[i];
}

template <typename T>
T splineCube (T x, int n, T h, T* xn, T* fxn, T a)
{
	T* M = new T [n+1];
	splineCubeVector (n, h, fxn, M);
	M[n] = 0;
	for (int i = n - 1; i > 0; --i)
		M[i] = M[i-1];
	M[0] = 0;
	int I = ceil ((x - a) / h);
	T	c1 = (fxn[I] - fxn[I-1]) / h - (M[I] - M[I-1]) * h / 6 - M[I-1] * (xn[I] + xn[I-1]) / 2,
		c2 = fxn[I-1] - M[I-1] * xn[I-1] * xn[I-1] / 2 - ((fxn[I] - fxn[I-1]) / h - (M[I] - M[I-1]) * h / 6 - M[I-1] * (xn[I] + xn[I-1]) / 2) * xn[I-1];
	T res = pow (x - xn[I-1], 3.0) / 6 / (xn[I] - xn[I-1]) * (M[I] - M[I-1]) + M[I-1] * x * x / 2 + c1 * x + c2;
	delete [] M;
	return res;
}

template <typename T>
T findRealResidual (T x, T px)
{
	return f(x) - px;
}

#endif