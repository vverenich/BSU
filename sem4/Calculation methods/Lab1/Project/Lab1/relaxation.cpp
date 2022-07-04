#include "relaxation.h"

Relaxation::Relaxation()
{

}

Matrix Relaxation::solveSystem(const Matrix &A_, const Matrix &b_, double param, size_t &numberOfIterations, std::vector<std::pair<size_t, double>> &iterationsNorms) const
{
    if(A_.getRowCount() != b_.getRowCount())
    {
        throw "Cannot solve, because matrixes have different row number";
    }

    Matrix A{A_};
    Matrix b{b_};

    // Making all the elements on the diagonal of Matrix A equal to 1
    for(size_t i{0}; i < A.getRowCount(); ++i)
    {
        double divisor{A.getMatrixElement(i, i)};

        for(size_t j{0}; j < A.getColumnCount(); ++j)
        {
            A.setMatrixElement(i, j, A.getMatrixElement(i, j) / divisor);
        }

        for(size_t j{0}; j < b.getColumnCount(); ++j)
        {
            b.setMatrixElement(i, j, b.getMatrixElement(i, j) / divisor);
        }
    }

    Matrix B{Matrix::getIdentityMatrix(A.getRowCount(), A.getColumnCount()) + (-A)};

    // Let's say x0^T = {1, 1, 1 ...}
    Matrix xPrev{b};
    for(size_t i{0}; i < xPrev.getRowCount(); ++i)
    {
        for(size_t j{0}; j < xPrev.getColumnCount(); ++j)
        {
            xPrev.setMatrixElement(i, j, 1);
        }
    }

    Matrix x{0.8*xPrev};

    const double EPSILON{0.00000001};
    size_t index{0};
    while((x + (-xPrev)).getNorm3() > EPSILON && index < 10)
    {
        xPrev = x;

        for(size_t i{0}; i < x.getRowCount(); ++i)
        {
            x.setMatrixElement(i, 0, (1-param) * xPrev.getMatrixElement(i, 0) + param * b.getMatrixElement(i, 0));

            size_t j{0};

            for(; j < i; ++j)
            {
                x.setMatrixElement(i, 0, x.getMatrixElement(i, 0) + param * x.getMatrixElement(j, 0) * B.getMatrixElement(i, j));
            }

            for(; j < A.getColumnCount(); ++j)
            {

                x.setMatrixElement(i, 0, x.getMatrixElement(i, 0) + param * xPrev.getMatrixElement(j, 0) * B.getMatrixElement(i, j));
            }
        }
        ++index;
        iterationsNorms.emplace_back(std::make_pair(index, (x+(-xPrev)).getNorm3()));
    }

    numberOfIterations = index;
    return x;
}
