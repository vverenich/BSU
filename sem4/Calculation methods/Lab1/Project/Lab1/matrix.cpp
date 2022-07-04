#include "matrix.h"

Matrix::Matrix() noexcept
{
}

Matrix::Matrix(const unsigned rowNumber, const unsigned columnNumber) noexcept
{
    m_matrix.resize(rowNumber);
    for (size_t i{0}; i < m_matrix.size(); ++i) {
        m_matrix.at(i).resize(columnNumber);
    }
}

Matrix::Matrix(const std::vector<std::vector<double> > &matrix)
{
    size_t columnCount{matrix.at(0).size()};
    for(size_t i{1}; i < matrix.size(); ++i)
    {
        if(matrix.at(i).size() != columnCount)
        {
            throw "Wrong parameters! Rows have to be equal.";
        }
    }

    m_matrix = matrix;
}

unsigned Matrix::getColumnCount() const
{
    return m_matrix.at(0).size();
}

unsigned Matrix::getRowCount() const
{
    return m_matrix.size();
}

void Matrix::setMatrixElement(const unsigned i, const unsigned j, const double value)
{
    m_matrix.at(i).at(j) = value;
}

double Matrix::getMatrixElement(const unsigned i, const unsigned j) const
{
    return m_matrix.at(i).at(j);
}

Matrix Matrix::getTransposedMatrix() const
{
    Matrix transposedMatrix(m_matrix.at(0).size(), m_matrix.size());

    for(size_t i{0}; i < transposedMatrix.getRowCount(); ++i)
    {
        for(size_t j{0}; j < transposedMatrix.getColumnCount(); ++j)
        {
            transposedMatrix.setMatrixElement(i, j, this->getMatrixElement(j, i));
        }
    }

    return transposedMatrix;
}

Matrix Matrix::getIdentityMatrix(const size_t rowNumber, const size_t columnNumber)
{
    if(rowNumber != columnNumber)
    {
        throw "Wrong parameters! Matrix has to be square.";
    }

    Matrix answer(rowNumber, columnNumber);

    for(size_t i{0}; i < rowNumber; ++i)
    {
        for(size_t j{0}; j != columnNumber; ++j)
        {
            if(i != j)
            {
                answer.setMatrixElement(i, j, 0);
            }
            else
            {
                answer.setMatrixElement(i, j, 1);
            }
        }
    }

    return answer;
}

double Matrix::getNorm3() const
{
    std::vector<double> rowSums(m_matrix.size());

    for(size_t i{0}; i < m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < m_matrix.at(0).size(); ++j)
        {
            rowSums.at(i) += std::abs(m_matrix.at(i).at(j));
        }
    }

    return *std::max_element(rowSums.begin(), rowSums.end());
}

void Matrix::getLUPdecomp(Matrix &L, Matrix &U, Matrix &P) const
{
    U = *this;
    P = getIdentityMatrix(getRowCount(), getColumnCount());
    L = P;

    // Getting upper triangle matrix U
    for(size_t i{0}; i < U.getColumnCount()-1; ++i)
    {

        // Searching for max element in row
        size_t indexOfAbsoluteMax{i};
        for(size_t j{i}; j < U.getColumnCount(); ++j)
        {
            if(std::abs(U.getMatrixElement(i, j)) > std::abs(U.getMatrixElement(i, indexOfAbsoluteMax)))
            {
                indexOfAbsoluteMax = j;
            }
        }

        if(indexOfAbsoluteMax != i)
        {
            U.swapColumns(i, indexOfAbsoluteMax);
            P.swapColumns(i, indexOfAbsoluteMax);
        }

        for(size_t j{i+1}; j < U.getRowCount(); ++j)
        {

            double multiplier{(-1) * U.getMatrixElement(j,i) / U.getMatrixElement(i, i)};

            // Some actions on matrix U
            for(size_t p{0}; p < U.getColumnCount(); ++p)
            {
                U.setMatrixElement(j, p, U.getMatrixElement(j, p) + multiplier * U.getMatrixElement(i, p));
            }

            L.setMatrixElement(j, i, -1 * multiplier);
        }
    }
}

void Matrix::getLDLtransposedDecomp(Matrix &L, Matrix &D, Matrix &Ltransposed) const
{
    Matrix A{*this};
    D = getIdentityMatrix(getRowCount(), getColumnCount());
    L = D;

    // Getting upper triangle matrix
    for(size_t i{0}; i < A.getColumnCount(); ++i)
    {
        for(size_t j{i+1}; j < A.getRowCount(); ++j)
        {

            double multiplier{(-1) * A.getMatrixElement(j,i) / A.getMatrixElement(i, i)};

            // Some actions on matrix A
            for(size_t p{0}; p < A.getColumnCount(); ++p)
            {
                A.setMatrixElement(j, p, A.getMatrixElement(j, p) + multiplier * A.getMatrixElement(i, p));
            }

            L.setMatrixElement(j, i, -1 * multiplier * sqrt(std::abs(A.getMatrixElement(i, i))));
        }

        L.setMatrixElement(i, i, sqrt(std::abs(A.getMatrixElement(i, i))));
        D.setMatrixElement(i, i, A.getMatrixElement(i, i) > 0 ? 1 : -1);
    }

    Ltransposed = L.getTransposedMatrix();
}

void Matrix::swapColumns(const size_t colIndex1, const size_t colIndex2)
{
    if(colIndex1 == colIndex2)
    {
        return;
    }

    for(size_t i{0}; i < getRowCount(); ++i)
    {
        double temp{getMatrixElement(i, colIndex1)};

        setMatrixElement(i, colIndex1, getMatrixElement(i, colIndex2));
        setMatrixElement(i, colIndex2, temp);
    }
}

void Matrix::swapRows(const size_t rowIndex1, const size_t rowIndex2)
{
    if(rowIndex1 == rowIndex2)
    {
        return;
    }

    for(size_t i{0}; i < getColumnCount(); ++i)
    {
        double temp{getMatrixElement(rowIndex1, i)};

        setMatrixElement(rowIndex1, i, getMatrixElement(rowIndex2, i));
        setMatrixElement(rowIndex2, i, temp);
    }
}

Matrix Matrix::operator*(const Matrix &y)
{
    if(getColumnCount() != y.getRowCount())
    {
        throw "Cannot multiply theese types of matrix";
    }

    Matrix b(getRowCount(), y.getColumnCount());

    for(size_t i{0}; i < getRowCount(); ++i)
    {
        for(size_t a{0}; a < y.getColumnCount(); ++a)
        {
            for(size_t j{0}; j < getColumnCount(); ++j)
            {
                b.m_matrix.at(i).at(a) += getMatrixElement(i, j) * y.getMatrixElement(j, a);
            }
        }
    }

    return b;
}

Matrix Matrix::operator-() const
{
    Matrix answer{*this};

    for(size_t i{0}; i < m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) *= -1;
        }
    }

    return answer;
}

bool operator==(const Matrix& m1, const Matrix& m2)
{
    if(m1.getColumnCount() != m2.getColumnCount() || m1.getRowCount() != m2.getRowCount())
    {
        return false;
    }

    for(size_t i{0}; i < m1.getRowCount(); ++i)
    {
        for(size_t j{0}; j < m1.getColumnCount(); ++j)
        {
            if(m1.getMatrixElement(i, j) != m2.getMatrixElement(i, j))
            {
                return false;
            }
        }
    }

    return true;
}

std::ostream& operator<<(std::ostream &os, const Matrix &matrix)
{
    for(const auto& row: matrix.m_matrix)
    {
        for(const auto& element: row){
            os << std::setprecision(4) << element << "\t\t";
        }
        os << "\n";
    }
    return os;
}

Matrix operator*(double a, const Matrix &A)
{
    Matrix answer{A};
    for(size_t i{0}; i < answer.m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < answer.m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) *= a;
        }
    }

    return answer;
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    if(A.getColumnCount() != B.getColumnCount() || A.getRowCount() != B.getRowCount())
    {
        throw "Wrong parameters! Matrixes have to be the same dimensions.";
    }

    Matrix answer{A};
    for(size_t i{0}; i < answer.m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < answer.m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) += B.m_matrix.at(i).at(j);
        }
    }

    return answer;
}
