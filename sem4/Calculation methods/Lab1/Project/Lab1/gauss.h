#ifndef GAUSS_H
#define GAUSS_H

#include "abstractgauss.h"

class Gauss : public AbstractGauss
{
public:
    Gauss();
    virtual Matrix solveSystem(const Matrix &A, const Matrix &b) const;
};

#endif // GAUSS_H
