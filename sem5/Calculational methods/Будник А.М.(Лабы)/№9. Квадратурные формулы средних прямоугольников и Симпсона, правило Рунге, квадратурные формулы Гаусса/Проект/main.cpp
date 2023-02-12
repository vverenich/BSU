#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;

void main ()
{
	ofstream out ("out.txt");
	const double eps = 0.00001;
	double	a = 1,
			b = 3,
			h,
			integral,
			r;
	int		n;

	integral = ExactIntegral (a, b);
	out << "Exact integral = " << fixed << setprecision (10) << integral;

	h = FindStepRect (a, b, eps);
	out << "\n\nRectangle.\n\nMinimal step = " << fixed << setprecision (10) << h;
	integral = IntegralRect (a, b, h);
	out << "\nIntegral = " << fixed << setprecision (10) << integral;
	r = FindResidual (a, b, integral);
	out << "\nResidual = " << fixed << setprecision (10) << r;

	h = FindStepSimpson (a, b, eps);
	out << "\n\nSimpson.\n\nMinimal step = " << fixed << setprecision (10) << h;
	integral = IntegralSimpson (a, b, h);
	out << "\nIntegral = " << fixed << setprecision (10) << integral;
	r = FindResidual (a, b, integral);
	out << "\nResidual = " << fixed << setprecision (10) << r;

	/*integral = IntegralRunge (a, b, h, eps);
	out << "\n\nRunge.\n\nMinimal step = " << fixed << setprecision (15) << h;
	out << "\nIntegral = " << fixed << setprecision (10) << integral;
	r = FindResidual (a, b, integral);
	out << "\nResidual = " << fixed << setprecision (15) << r;*/

	n = FindStepGauss (b, eps);
	out << "\n\nGauss.\n\nMinimal number of nodes = " << n;
	integral = IntegralGauss (a, b);
	out << "\nIntegral = " << fixed << setprecision (10) << integral;
	r = FindResidual (a, b, integral);
	out << "\nReal residual = " << fixed << setprecision (15) << r;

	out.close();
}