#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;

void main ()
{
	ofstream out ("out.txt");
	const int n = 5;
	double	*x = new double [n+1],
			*fx = new double [n+1],
			*fdifx = new double [n+1],
			xf = 1,
			xl = 3,
			a1,
			a2,
			a3,
			pa1,
			pa2,
			pa3,
			**rr = new double* [n+1];
	for (int i = 0; i <= n; ++i)
		rr[i] = new double [n+1];

	createNodes (n, x, fx, fdifx, xf, xl);
	out << "\n" << n+1 << " nodes:\n\n";
	for (int i = 0; i <= n; ++i)
		out << setw (10) << x[i];
	out << "\n";
	for (int i = 0; i <= n; ++i)
		out << setw (10) << fx[i];
	out << "\n";
	for (int i = 0; i <= n; ++i)
		out << setw (10) << fdifx[i];
	createMatrix (n, rr, x, fx, fdifx);
	out << "\n\nRR matrix:\n\n";
	printRRmatrix (rr, n, out, 10);
	a1 = 1.1333;//xf + (xl - xf) / 6;
	a2 = 1.9333;//x[n/2] + (xl - xf) / 6;
	a3 = 2.8666;//xl - (xl - xf) / 6;
	pa1 = Ermit (a1, n, x, rr);
	pa2 = Ermit (a2, n, x, rr);
	pa3 = Ermit (a3, n, x, rr);
	out << "\nP(x0+h/3) = P(" << a1 << ") = " << pa1 << ".\n";
	out << "Real residual : " << findRealResidual (a1, pa1) << ".\n";
	out << "Theoretical residual : " << findTheoreticalResidual (a1, n, x, rr) << ".\n\n";
	out << "P(x[n/2]+h/3) = P(" << a2 << ") = " << pa2 << ".\n";
	out << "Real residual : " << findRealResidual (a2, pa2) << ".\n";
	out << "Theoretical residual : " << findTheoreticalResidual (a2, n, x, rr) << ".\n\n";
	out << "P(xn-h/3) = P(" << a3 << ") = " << pa3 << ".\n";
	out << "Real residual : " << findRealResidual (a3, pa3) << ".\n";
	out << "Theoretical residual : " << findTheoreticalResidual (a3, n, x, rr) << ".\n\n";

	delete [] x;
	delete [] fx;
	delete [] fdifx;
	for (int i = 0; i <= n; ++i)
		delete [] rr[i];
	delete [] rr;
}