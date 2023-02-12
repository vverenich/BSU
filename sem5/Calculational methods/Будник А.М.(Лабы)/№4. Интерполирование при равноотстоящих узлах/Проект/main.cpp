#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;

void main ()
{
	ofstream out ("out.txt");
	const int n = 5, m = 10;
	double	*xn = new double [n+1],
			*xm = new double [m+1],
			*fxn = new double [n+1],
			*fxm = new double [m+1],
			h,
			xf = 1,
			xl = 3,
			a1,
			a2,
			a3,
			pa1,
			pa2,
			pa3,
			**krn = new double* [n+1],
			**krm = new double* [m+1];
	for (int i = 0; i <= n; ++i)
		krn[i] = new double [n+1];
	for (int i = 0; i <= m; ++i)
		krm[i] = new double [m+1];

	createNodes (n, xn, fxn, xf, xl, h);
	createMatrix (n, krn, fxn);
	out << "KR matrix:\n\n";
	printKRmatrix (krn, n, out, 10);
	out << "\n" << n+1 << " nodes:\n\n";
	for (int i = 0; i <= n; ++i)
		out << setw (10) << xn[i];
	out << "\n";
	for (int i = 0; i <= n; ++i)
		out << setw (10) << fxn[i];
	a1 = xf + h / 3;
	a2 = xn[n/2] + h / 3;
	a3 = xl - h / 3;
	pa1 = beginning (a1, n, krn, xf, h);
	pa2 = center (a2, n, krn, xn, h);
	pa3 = ending (a3, n, krn, xl, h);
	out << "\n\nP(x0+h/3) = P(" << a1 << ") = " << pa1 << ".\n";
	out << "Real residual : " << findRealResidual (a1, pa1) << ".\n\n";
	out << "P(x[n/2]+h/3) = P(" << a2 << ") = " << pa2 << ".\n";
	out << "Real residual : " << findRealResidual (a2, pa2) << ".\n\n";
	out << "P(xn-h/3) = P(" << a3 << ") = " << pa3 << ".\n";
	out << "Real residual : " << findRealResidual (a3, pa3) << ".\n\n";

	createNodes (m, xm, fxm, xf, xl, h);
	createMatrix (m, krm, fxm);
	out << "KR matrix:\n\n";
	printKRmatrix (krm, m, out, 15);
	out << "\n" << m+1 << " nodes:\n\n";
	for (int i = 0; i <= m; ++i)
		out << setw (10) << xm[i];
	out << "\n";
	for (int i = 0; i <= m; ++i)
		out << setw (10) << fxm[i];
	a1 = xf + h / 3;
	a2 = xm[n/2] + h / 3;
	a3 = xl - h / 3;
	pa1 = beginning (a1, m, krm, xf, h);
	pa2 = center (a2, m, krm, xm, h);
	pa3 = ending (a3, m, krm, xl, h);
	out << "\n\nP(x0+h/3) = P(" << a1 << ") = " << pa1 << ".\n";
	out << "Real residual : " << findRealResidual (a1, pa1) << ".\n\n";
	out << "P(x[n/2]+h/3) = P(" << a2 << ") = " << pa2 << ".\n";
	out << "Real residual : " << findRealResidual (a2, pa2) << ".\n\n";
	out << "P(xn-h/3) = P(" << a3 << ") = " << pa3 << ".\n";
	out << "Real residual : " << findRealResidual (a3, pa3) << ".\n\n";

	delete [] xn;
	delete [] xm;
	delete [] fxn;
	delete [] fxm;
	for (int i = 0; i <= n; ++i)
		delete [] krn[i];
	for (int i = 0; i <= m; ++i)
		delete [] krm[i];
	delete [] krn;
	delete [] krm;
}