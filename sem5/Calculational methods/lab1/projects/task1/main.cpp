#include <iostream>
#include <fstream>
#include <iomanip>

#include "functions.h"

int main ()
{
    std::ofstream out ("out.txt");
    const int m = 10;
    double	*xm = new double [m+1],
            *fxm = new double [m+1],
            h,
            xf = 0.3,
            xl = 1.3,
            a1,
            a2,
            a3,
            pa1,
            pa2,
            pa3,
            **rrm = new double* [m+2];
    for (int i = 0; i <= m+1; ++i)
        rrm[i] = new double [m+2];

    createNodes (m, xm, fxm, xf, xl, h);

    out << m+1 << "interpolation nodes:\n\n";
    for (int i = 0; i <= m; ++i) {
        out << std::setw (10) << xm[i];
    }
    out << "\n";

    for (int i = 0; i <= m; ++i) {
        out << std::setw (10) << fxm[i];
    }

    a1 = xf + 2 * h / 3;
    a2 = xm[m/2] + h / 2;
    a3 = xl - h / 3;

    pa1 = lagrangePolynomial(a1, m, xm, fxm);
    pa2 = lagrangePolynomial(a2, m, xm, fxm);
    pa3 = lagrangePolynomial(a3, m, xm, fxm);

    createMatrix (m, rrm, xm, fxm);
    out << "\nDivided difference table:\n\n";
    printRRmatrix (rrm, m, out, 15);

    out << "\n\nP(x0+2*h/3) = P(" << a1 << ") = " << pa1 << ".\n";
    out << "Real residual : " << getRealResidual (a1, pa1) << ".\n";
    out << "Theoretical residual : " << getTheoreticalResidualNewton(a1, m, xm, rrm) << ".\n\n";
    out << "P(x[n/2]+h/2) = P(" << a2 << ") = " << pa2 << ".\n";
    out << "Real residual : " << getRealResidual (a2, pa2) << ".\n";
    out << "Theoretical residual : " << getTheoreticalResidualNewton(a2, m, xm, rrm) << ".\n\n";
    out << "P(xn-h/3) = P(" << a3 << ") = " << pa3 << ".\n";
    out << "Real residual : " << getRealResidual (a3, pa3) << ".\n";
    out << "Theoretical residual : " << getTheoreticalResidualNewton(a3, m, xm, rrm) << ".\n\n";

    delete [] xm;
    delete [] fxm;
    for (int i = 0; i <= m+1; ++i) {
        delete [] rrm[i];
    }
    delete [] rrm;
}
