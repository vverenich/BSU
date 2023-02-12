#include <iostream>
#include <fstream>
#include "functions.h"
using namespace std;

void main ()
{
	const double eps = 0.000001, delta = 0.01;
	double* x = new double [2];
	ofstream out ("out.txt");
	CreatePoint (x, 0.0, 1.0, delta);
	out << "x0 = (" << x[0] << ", " << x[1] << ").\n\n";
	int numIter = Newton (x, eps);
	out << "x = (" << x[0] << ", " << x[1] << ").\n\n";
	out << numIter << " iterations.\n\n";
	out << "residual: " << findResidual (x) << ".\n\n";
	delete [] x;
}