#include "abstractgauss.h"


void AbstractGauss::swapRows(Matrix &A, Matrix &b, const size_t rowIndex1, const size_t rowIndex2) const
{
    if(rowIndex1 == rowIndex2)
    {
        return;
    }

    if(A.getRowCount() != b.getRowCount())
    {
        throw "Cannot swap, because matrixes have different row number";
    }

    // Swapping rows in matrix A
    for(size_t i{0}; i < A.getColumnCount(); ++i)
    {
        double temp{A.getMatrixElement(rowIndex1, i)};

        A.setMatrixElement(rowIndex1, i, A.getMatrixElement(rowIndex2, i));
        A.setMatrixElement(rowIndex2, i, temp);
    }

    // Swapping rows in matrix b
    for(size_t i{0}; i < b.getColumnCount(); ++i)
    {
        double temp{b.getMatrixElement(rowIndex1, i)};

        b.setMatrixElement(rowIndex1, i, b.getMatrixElement(rowIndex2, i));
        b.setMatrixElement(rowIndex2, i, temp);
    }
}
