#include <fstream>
#include <iomanip>
#include "functions.h"
using namespace std;
    
int main ()
{
    ofstream out ("out.txt");
    double	a = 0.3,
            b = 1,
            integral,
            r,
            t;
    int		n = 3;

    integral = ExactIntegral (a, b);
    out << "Exact integral = " << fixed << setprecision (10) << integral;

    out << "\n\nGauss:\n";
    integral = IntegralGauss (a, b);
    out << "\nIntegral = " << fixed << setprecision (10) << integral;
    r = FindResidual (a, b, integral);
    out << "\nReal residual = " << fixed << setprecision (15) << r;
    t = getTheoreticalDifferenceByGauss(n, a, b);
    out << "\nTheoretical residual = " << fixed << setprecision (15) << t;

    out << "\n\nTrapezoid:\n";
    double trapezoidResult = trapezoid(a, b);
    out << "\nIntegral = " << fixed << setprecision (10) << trapezoidResult;
    double trapezoidResidual = FindResidual (a, b, trapezoidResult);
    out << "\nReal residual = " << fixed << setprecision (15) << trapezoidResidual;
    double trapezoidTheoreticalResidual = getTheoreticalDifferenceByTrapezoid(a, b);
    out << "\nTheoretical residual = " << fixed << setprecision (15) << trapezoidTheoreticalResidual;

    out.close();
}
