#ifndef GAUSSJORDAN_H
#define GAUSSJORDAN_H

#include <abstractgauss.h>

class GaussJordan : public AbstractGauss
{
public:
    GaussJordan();
    virtual Matrix solveSystem(const Matrix &A, const Matrix &b) const override final;
};

#endif // GAUSSJORDAN_H
