#ifndef GAUSSCOLUMNSELECTION_H
#define GAUSSCOLUMNSELECTION_H

#include "abstractgauss.h"

class GaussColumnSelection : public AbstractGauss
{
public:
    GaussColumnSelection();
    virtual Matrix solveSystem(const Matrix &A, const Matrix &b) const override final;

    //void swapRows(Matrix &A, Matrix &b, const size_t rowIndex1, const size_t rowIndex2) const;
};

#endif // GAUSSCOLUMNSELECTION_H
