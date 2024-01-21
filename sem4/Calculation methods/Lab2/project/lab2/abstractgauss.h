#ifndef ABSTRACTGAUSS_H
#define ABSTRACTGAUSS_H

#include<matrix.h>

class AbstractGauss
{
public:
    virtual ~AbstractGauss(){};
    virtual Matrix solveSystem(const Matrix &A, const Matrix &b) const = 0;

    void swapRows(Matrix &A, Matrix &b, const size_t rowIndex1, const size_t rowIndex2) const;
};

#endif // ABSTRACTGAUSS_H
