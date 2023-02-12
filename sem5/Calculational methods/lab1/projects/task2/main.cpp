#include <fstream>
#include <iomanip>

#include "functions.h"

using namespace std;

int main ()
{
    ofstream out ("out.txt");
    const int n = 3;
    double	*xn = new double [n+1],
            *fxn = new double [n+1],
            h,
            xf = 0.3,
            xl = 0.6,
            a1,
            a2,
            a3,
            pa1,
            pa2,
            pa3,
            **krn = new double* [n+1];
    for (int i = 0; i <= n; ++i) {
        krn[i] = new double [n+1];
    }

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

    a1 = xf + 2 * h / 3;

    pa1 = beginning (a1, n, krn, xf, h);
    pa2 = center (a2, n, krn, xn, h);
    pa3 = ending (a3, n, krn, xl, h);
    out << "\n\nP(x0+2*h/3) = P(" << a1 << ") = " << pa1 << ".\n";
    out << "Real residual : " << findRealResidual (a1, pa1) << ".\n";
    out << "Theoretical residual : " << findTheoreticalResidual(n + 1, xn, a1) << ".\n\n";

    delete [] xn;
    delete [] fxn;
    for (int i = 0; i <= n; ++i)
        delete [] krn[i];
    delete [] krn;
}
