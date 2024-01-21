#include "gaussjordan.h"

GaussJordan::GaussJordan()
{

}

Matrix GaussJordan::solveSystem(const Matrix &A, const Matrix &b) const
{
    if(A.getRowCount() != b.getRowCount())
    {
        throw "Cannot solve, because matrixes have different row number";
    }

    Matrix A_{A};
    Matrix b_{b};

    // Getting upper triangle matrix
    for(size_t i{0}; i < A_.getColumnCount()-1; ++i)
    {
        for(size_t j{i+1}; j < A_.getRowCount(); ++j)
        {

            double multiplier{(-1) * A_.getMatrixElement(j,i) / A_.getMatrixElement(i, i)};

            // Some actions on matrix A
            for(size_t p{0}; p < A.getColumnCount(); ++p)
            {
                A_.setMatrixElement(j, p, A_.getMatrixElement(j, p) + multiplier * A_.getMatrixElement(i, p));
            }

            // The same actions on matrix b
            for(size_t p{0}; p < b_.getColumnCount(); ++p)
            {
                b_.setMatrixElement(j, p, b_.getMatrixElement(j, p) + multiplier * b_.getMatrixElement(i, p));
            }
        }
    }

    // Nulling all the elements that are higher than the diagonal
    for(int i{(int)A_.getColumnCount()-1}; i > 0 ; --i)
    {
        for(int j{(int)i - 1}; j >= 0; --j)
        {
            double multiplier{(-1) * A_.getMatrixElement(j,i) / A_.getMatrixElement(i, i)};

            // Some actions on matrix A
            for(size_t p{0}; p < A_.getColumnCount(); ++p)
            {
                A_.setMatrixElement(j, p, A_.getMatrixElement(j, p) + multiplier * A_.getMatrixElement(i, p));
            }

            // The same actions on matrix b
            for(size_t p{0}; p < b_.getColumnCount(); ++p)
            {
                b_.setMatrixElement(j, p, b_.getMatrixElement(j, p) + multiplier * b_.getMatrixElement(i, p));
            }
        }
    }

    // Making all the diagonal elements equal to 1
    for(size_t i{0}; i < A_.getRowCount(); ++i)
    {
        double divisor{A_.getMatrixElement(i, i)};

        // Some actions on matrix A
        for(size_t j{0}; j < A_.getColumnCount(); ++j)
        {
            A_.setMatrixElement(i, j, A_.getMatrixElement(i,j) / divisor);
        }

        // The same actions on matrix b
        for(size_t j{0}; j < b_.getColumnCount(); ++j)
        {
            b_.setMatrixElement(i, j, b_.getMatrixElement(i,j) / divisor);
        }
    }

    return b_;
}
