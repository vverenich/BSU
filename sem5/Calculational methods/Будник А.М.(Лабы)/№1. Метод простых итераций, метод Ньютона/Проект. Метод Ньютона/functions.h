#ifndef FUNCTIONS_H
#define FUNCTIONS_H

template <typename T>
T f1 (T* x)
{
	return (pow(x[0], 3) + pow(x[1], 3) - 6.5 * x[0] + 3);
}

template <typename T>
T f2 (T* x)
{
	return (pow(x[0], 3) - pow(x[1], 3) - 6.5 * x[1] + 2);
}

template <typename T>
T df1dx (T* x)
{
	return (3 * x[0] * x[0] - 6.5);
}

template <typename T>
T df1dy (T* x)
{
	return (3 * x[1] * x[1]);
}

template <typename T>
T df2dx (T* x)
{
	return (3 * x[0] * x[0]);
}

template <typename T>
T df2dy (T* x)
{
	return (-3 * x[1] * x[1] - 6.5);
}

template <typename T>
T det (T* x)
{
	return df1dx(x) * df2dy(x) - df1dy(x) * df2dx(x);
}

template <typename T>
int Newton (T* x, T eps)
{
	int numIter = 0;
	do
	{
		++numIter;
		T tmp = x[0] - (df2dy(x) * f1(x) - df1dy(x) * f2(x)) / det(x);
		x[1] -= (df1dx(x) * f2(x) - df2dx(x) * f1(x)) / det(x);
		x[0] = tmp;
	} while (findResidual (x) > eps);
	return numIter;
}

template <typename T>
T normVCube (T* r)
{
	return max (abs (r[0]), abs (r[1]));
}

template <typename T>
T findResidual (T* x)
{
	return max (abs (f1(x)), abs (f2(x)));
}

template <typename T>
T g (T y)
{
	return (2 * pow (y, 3) + 6.5 * y + 1) / 6.5;
}

template <typename T>
void CreatePoint (T* x, T a, T b, T delta)
{
	T length = b - a;
	T arr [2];
	T arrmid [2];
	while (length > delta)
	{
		T mid = (a + b) / 2;
		arr[0] = g(a);
		arr[1] = a;
		arrmid[0] = g(mid);
		arrmid[1] = mid;
		if (f2(arr) * f2(arrmid) < 0)
			b = mid;
		else
			a = mid;
		length = b - a;
	}
	x[0] = g(a);
	x[1] = a;
}

#endif