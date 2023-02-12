#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;

void main ()
{
	ofstream out ("out.txt");
	const int	n = 3,
				N = 6;
	double	*x = new double [N],
			*fx = new double [N],
			*b = new double [n+1],
			*coef = new double [n+1],
			h,
			xf = 1,
			xl = 3,
			a1,
			a2,
			a3,
			pa1,
			pa2,
			pa3,
			**A = new double* [n+1];
	for (int i = 0; i <= n; ++i)
		A[i] = new double [n+1];

	createNodes (N, x, fx, xf, xl, h);
	out << N << " nodes:\n\n";
	for (int i = 0; i < N; ++i)
		out << setw (10) << x[i];
	out << "\n";
	for (int i = 0; i < N; ++i)
		out << setw (10) << fx[i];
	out << "\n\nCoefficients:\n\n";
	createMatrix (n, N, x, A, b, fx);
	a1 = x[0] + h / 3;
	a2 = x[(N-1)/2] + h / 3;
	a3 = x[N-1] - h / 3;
	FindCoefficients (n, A, b, coef);
	for (int i = 0; i <= n; ++i)
		out << setw (10) << coef[i] << " ";
	pa1 = Polynom (a1, n, coef);
	pa2 = Polynom (a2, n, coef);
	pa3 = Polynom (a3, n, coef);
	out << "\n\nP(x[0]+h/3) = P(" << a1 << ") = " << pa1 << ".\n";
	out << "Real residual : " << findRealResidual (a1, pa1) << ".\n\n";
	out << "P(x[n/2]+h/3) = P(" << a2 << ") = " << pa2 << ".\n";
	out << "Real residual : " << findRealResidual (a2, pa2) << ".\n\n";
	out << "P(xn-h/3) = P(" << a3 << ") = " << pa3 << ".\n";
	out << "Real residual : " << findRealResidual (a3, pa3) << ".\n\n";

	delete [] x;
	delete [] fx;
	delete [] b;
	delete [] coef;
	for (int i = 0; i <= n; ++i)
		delete [] A[i];
	delete [] A;
}