#ifndef RELAXATION_H
#define RELAXATION_H

#include "matrix.h"


class Relaxation
{
public:
    Relaxation();

    Matrix solveSystem(const Matrix &A, const Matrix &b, double param, size_t &numberOfIterations, std::vector<std::pair<size_t, double>> &) const;
};

#endif // RELAXATION_H
