#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f (T x)
{
	return 8 * exp(x) - 7 * cos(x);
}

template <typename T>
T ExactIntegral (T a, T b)
{
	return 8 * (exp(b) - exp(a)) + 7 * (sin(a) - sin(b));
}

template <typename T>
T fdifmax (int k, T b)
{
	switch (k % 4)
	{
	case 0:
		return 8 * exp(b) - 7 * cos(b);
	case 1:
		return 8 * exp(b) + 7 * sin(b);
	case 2:
		return 8 * exp(b) + 7 * cos(b);
	case 3:
		return 8 * exp(b) - 7 * sin(b);
	}
}

template <typename T>
T FindStepRect (T a, T b, T eps)
{
	int n = ceil (sqrt (pow (b - a, 3.0) * fdifmax (2, b) / 24 / eps));
	return (b - a) / n;
}

template <typename T>
T FindStepSimpson (T a, T b, T eps)
{
	int n = ceil (pow (pow (b - a, 5.0) * fdifmax (4, b) / 180 / eps, 0.25));
	return (b - a) / n;
}

template <typename T>
int FindStepGauss (T b, T eps)
{
	int n = 1;
	T R = 1;
	while (R * fdifmax (2 * n, b) / (2 * n + 1) > eps)
	{
		++n;
		R *= (4 * pow (n, 4.0) / pow (2 * n * (2 * n - 1), 3.0));
	}
	return n;
}

template <typename T>
T IntegralRect (T a, T b, T h)
{
	T integral = 0;
	for (T pt = a + h / 2; pt < b; pt += h)
		integral += f (pt);
	return h * integral;
}

template <typename T>
T IntegralSimpson (T a, T b, T h)
{
	T	integral1 = 0,
		integral2 = 0;
	for (T pt = a + h; pt < b; pt += 2 * h)
		integral1 += f (pt);
	for (T pt = a + 2 * h; pt < b; pt += 2 * h)
		integral2 += f (pt);
	return h / 3 * (f (a) + f (b) + 4 * integral1 + 2 * integral2);
}

template <typename T>
T IntegralLeftRect (T a, T b, T h)
{
	T integral = 0;
	for (T pt = a; pt < b; pt += h)
		integral += f (pt);
	return h * integral;
}

template <typename T>
T IntegralRunge (T a, T b, T& h, T eps)
{
	h = b - a;
	T	f1,
		f2 = IntegralLeftRect (a, b, h);
	do
	{
		f1 = f2;
		h /= 2;
		f2 = IntegralLeftRect (a, b, h);
	} while (abs (f2 - f1) * 2 > eps);
	return 2 * f2 - f1;
}

template <typename T>
T IntegralGauss (T a, T b, const int n = 5)
{
	T	*t = new T [n],
		*A = new T [n];
	t[0] = -0.9061798459;
	t[1] = -0.5384693101;
	t[2] = 0;
	t[3] = 0.5384693101;
	t[4] = 0.9061798459;
	A[0] = A[4] = 0.2369268851;
	A[1] = A[3] = 0.4786286705;
	A[2] = 0.5688888899;
	T integral = 0;
	for (int i = 0; i < n; ++i)
		integral += A[i] * f ((a + b + (b - a) * t[i]) / 2);
	return integral * (b - a) / 2;
	delete [] A;
	delete [] t;
}

template <typename T>
T FindResidual (T a, T b, T integral)
{
	return ExactIntegral (a, b) - integral;
}

#endif