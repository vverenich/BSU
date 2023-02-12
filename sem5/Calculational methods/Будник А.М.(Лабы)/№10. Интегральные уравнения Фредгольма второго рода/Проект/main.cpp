#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;

void main ()
{
	ofstream out ("out.txt");
	const int	n = 10,
				M5 = 5,
				M10 = 10; // количество отрезков
	double	*y = new double [n+1],
			a = 0,
			b = 1,
			x = (b - a) / 2.1,
			l = 0.3,
			res;
	
	res = Quadrature (x, a, b, l, n, y);
	out << fixed << setprecision (10) << "Quadrature            : u(x*) = u(" << x << ") = " << res << "\nf(xi): ";
	for (int i = 0; i <= n; ++i)
		out << setw (15) << y[i];

	res = Approximation (x, M5, a, b, l, n, y);
	out << "\n\nApproximation (M = 5) : u(x*) = u(" << x << ") = " << res << "\nf(xi): ";
	for (int i = 0; i <= n; ++i)
		out << setw (15) << y[i];

	res = Approximation (x, M10, a, b, l, n, y);
	out << "\n\nApproximation (M = 10): u(x*) = u(" << x << ") = " << res << "\nf(xi): ";
	for (int i = 0; i <= n; ++i)
		out << setw (15) << y[i];

	out.close();
	delete [] y;
}