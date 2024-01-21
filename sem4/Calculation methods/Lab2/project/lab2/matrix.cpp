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

Matrix::Matrix(const std::vector<std::vector<std::complex<double>>> &matrix)
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

Matrix::Matrix(Matrix &&m)
{
    m_matrix = m.m_matrix;
}

Matrix &Matrix::operator=(Matrix &&a)
{
    if(this == &a)
    {
        return *this;
    }

    m_matrix = std::move(a.m_matrix);
    return *this;
}

unsigned Matrix::getColumnCount() const
{
    return m_matrix.at(0).size();
}

unsigned Matrix::getRowCount() const
{
    return m_matrix.size();
}

void Matrix::setMatrixElement(const unsigned i, const unsigned j, const std::complex<double> value)
{
    m_matrix.at(i).at(j) = value;
}

std::complex<double> Matrix::getMatrixElement(const unsigned i, const unsigned j) const
{
    return m_matrix.at(i).at(j);
}
/*
std::pair<Matrix, std::complex<double>> Matrix::getMaxEigenvalueAndEigenvector()
{
    auto pair{getMaxEigenvalueAndEigenvectorCase1()};
    std::cout << pair.first << "\n";
    std::cout <<pair.second <<"\n";

}

std::pair<Matrix, double> Matrix::getMaxEigenvalueAndEigenvectorCase1()
{
    // Random vector
    Matrix y0{getRowCount(), 1};

    // Fill vector y0 with 1
    for(size_t i{0}; i < y0.getRowCount(); ++i)
    {
        for(size_t j{0}; j < y0.getColumnCount(); ++j)
        {
            y0.setMatrixElement(i, j, 1);
        }
    }

    Matrix u{y0};
    Matrix v{y0};
    Matrix A{*this};
    double lambda{0};

    const double EPSILON{0.001};

    while((A * u  + (lambda) * u).getNorm3() > EPSILON)
    {
        v = A * u;
        lambda = v.getMaxModuloElement();
        u = (1.0 / lambda) * v;
    }

    return std::make_pair(u, lambda);
}
*/
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

double Matrix::getNorm2() const
{
    double sumOfSquares{0};
    for(size_t i{0}; i < getRowCount(); ++i)
    {
        for(size_t j{0}; j < getColumnCount(); ++j)
        {
            sumOfSquares += real(getMatrixElement(i, j) * getMatrixElement(i, j));
        }
    }

    return std::sqrt(sumOfSquares);
}

std::complex<double> Matrix::getMaxModuloElement()
{
    double maxModuloElement{-1};
    for(size_t i {0}; i < getRowCount(); ++i)
    {
        for(size_t j {0}; j < getColumnCount(); ++j)
        {
            if(std::abs(getMatrixElement(i, j)) > maxModuloElement)
            {
                maxModuloElement = std::abs(getMatrixElement(i, j));
            }
        }
    }

    return maxModuloElement;
}

void Matrix::toHessenbergForm()
{
    if(getColumnCount() != getRowCount())
    {
        throw "You cannot transform matrix to Hessenberg form if it is not square.";
    }

    // Reflection method
    for(size_t j{0}; j < getColumnCount() - 2; ++j)
    {
        // Getting vector x and filling it
        Matrix x{getRowCount() - (unsigned)j - 1, 1};
        for(size_t i{0}; i < x.getRowCount(); ++i)
        {
            x.setMatrixElement(i, 0, getMatrixElement(i + j + 1, j));
        }

        // Getting vector w and filling it
        Matrix w{getRowCount() - (unsigned)j - 1, 1};
        w.setMatrixElement(0, 0, x.getNorm2());

        // Getting vector v
        Matrix v{w + -x};

        // Getting matrix P
        Matrix P{v * v.getTransposedMatrix()};
        Matrix k{v.getTransposedMatrix() * v};
        auto coefficient = static_cast<std::complex<double>>(1) / k.getMatrixElement(0, 0);
        P = coefficient * P;

        Matrix H_ = Matrix::getIdentityMatrix(P.getRowCount(), P.getColumnCount()) + -static_cast<std::complex<double>>(2) * P;

        // Getting matrix H
        Matrix H {Matrix::getIdentityMatrix(getRowCount(), getColumnCount())};
        for(size_t i{0}; i < H_.getRowCount(); ++i)
        {
            for(size_t k{0}; k < H_.getColumnCount(); ++k)
            {
                H.setMatrixElement(i + j + 1, k + j + 1, H_.getMatrixElement(i, k));
            }
        }

        *this = H * (*this) * H;
    }
}

std::pair<Matrix, Matrix> Matrix::QRdecomposition() const
{
    if(getColumnCount() != getRowCount())
    {
        throw "You cannot transform matrix to Hessenberg form if it is not square.";
    }


    Matrix R{*this};
    Matrix Q{Matrix::getIdentityMatrix(getRowCount(), getColumnCount())};
    Matrix Q_{Matrix::getIdentityMatrix(getRowCount(), getColumnCount())};

    // Filling the array
    for(size_t j{0}; j < getColumnCount()-1; ++j)
    {
        // Calculating cos and sin
        auto alpha = R.getMatrixElement(j, j);
        auto beta = R.getMatrixElement(j + 1, j);

        auto cos = alpha / std::sqrt(alpha * alpha + beta * beta);
        auto sin = beta / std::sqrt(alpha * alpha + beta * beta);

        // Modify matrix
        Q_.setMatrixElement(j, j, cos);
        Q_.setMatrixElement(j + 1, j + 1, cos);
        Q_.setMatrixElement(j + 1, j, -sin);
        Q_.setMatrixElement(j, j + 1, sin);

        R = Q_*R;

        Q = Q * Q_.getTransposedMatrix();

        Q_.setMatrixElement(j, j, 1);
        Q_.setMatrixElement(j + 1, j + 1, 1);
        Q_.setMatrixElement(j + 1, j, 0);
        Q_.setMatrixElement(j, j + 1, 0);
    }

    return std::make_pair(Q, R);
}

std::vector<std::complex<double>> Matrix::getEigenvaluesQRalgorithm() const
{
    // QR-algorithm
    Matrix A{*this};

    std::vector<std::complex<double>> eigenvaluesCurrent(getColumnCount());
    std::vector<std::complex<double>> eigenvaluesPrevious(getColumnCount());
    double maxModuloValue{std::numeric_limits<double>::max()};

    const double EPSILON{1e-5};
    while (maxModuloValue >= EPSILON )
    {
        auto QR{A.QRdecomposition()};
        A = QR.second * QR.first;

        maxModuloValue = 0;
        // Filling vector with new values
        for(size_t j{0}; j < eigenvaluesCurrent.size(); ++j)
        {
            // The situation, when the element below the diagonal one is approximately
            // equal to 0. It means that the diagonal one is eigenvalue
            double moduloOfElementBelow{};
            if(j + 1 <= eigenvaluesCurrent.size() - 1)
            {
                moduloOfElementBelow = std::abs(A.getMatrixElement(j + 1, j));
            }
            if((-EPSILON <= moduloOfElementBelow && moduloOfElementBelow <= EPSILON) ||
               j == eigenvaluesCurrent.size() - 1)
            {
                // Filling the vector of current eigenvalues
                eigenvaluesCurrent.at(j) = A.getMatrixElement(j, j);

                // Difference modulus between corresponding elements at iterations
                auto diff{std::abs(eigenvaluesCurrent.at(j) - eigenvaluesPrevious.at(j))};

                // Update maxModulo if needed
                maxModuloValue = std::max(diff, maxModuloValue);
            }
            else{

                // The situation, when there is 2x2 block on the diagonal
                auto a{A.getMatrixElement(j, j)};
                auto b{A.getMatrixElement(j, j + 1)};
                auto c{A.getMatrixElement(j + 1, j)};
                auto d{A.getMatrixElement(j + 1, j + 1)};

                std::complex<double> sqrtDiscriminant{std::sqrt((a+d) * (a+d) - (std::complex<double>)4 * (a*d - b*c))};
                eigenvaluesCurrent.at(j) = ((a+d) + sqrtDiscriminant)/(std::complex<double>)2;
                eigenvaluesCurrent.at(j+1) = ((a+d) - sqrtDiscriminant)/(std::complex<double>)2;

                // Difference modulus between corresponding elements at iterations in j and j+1 pos
                auto diffJ{std::abs(eigenvaluesCurrent.at(j) - eigenvaluesPrevious.at(j))};
                auto diffJ1{std::abs(eigenvaluesCurrent.at(j+1) - eigenvaluesPrevious.at(j+1))};

                // Update maxModulo if needed
                maxModuloValue = std::max(diffJ, maxModuloValue);
                maxModuloValue = std::max(diffJ1, maxModuloValue);

                ++j;
            }
        }

        eigenvaluesPrevious = eigenvaluesCurrent;
    }

    return eigenvaluesCurrent;
}


Matrix Matrix::getRandomMatrix(const size_t height, const size_t length)
{
    Matrix A{(unsigned)height, (unsigned)length};

    for(size_t i{0}; i < height; ++i)
    {
        for(size_t j{0}; j < length; ++j)
        {
            A.setMatrixElement(i, j, rand() % 7 - 3);
        }
    }

    return A;
}

/*
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
*/
void Matrix::swapColumns(const size_t colIndex1, const size_t colIndex2)
{
    if(colIndex1 == colIndex2)
    {
        return;
    }

    for(size_t i{0}; i < getRowCount(); ++i)
    {
        std::complex<double> temp{getMatrixElement(i, colIndex1)};

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
        std::complex<double> temp{getMatrixElement(rowIndex1, i)};

        setMatrixElement(rowIndex1, i, getMatrixElement(rowIndex2, i));
        setMatrixElement(rowIndex2, i, temp);
    }
}

Matrix Matrix::operator*(const Matrix &y) const
{
    if(getColumnCount() == 1 && getRowCount() == 1)
    {
        Matrix b(y);
        return getMatrixElement(0, 0) * (b);
    }

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
    Matrix answer{getRowCount(), getColumnCount()};

    for(size_t i{0}; i < m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) = static_cast<std::complex<double>>(-1) * m_matrix.at(i).at(j);
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

    return m1.m_matrix == m2.m_matrix;
    /*
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
    */
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

Matrix operator*(std::complex<double> a, const Matrix &A)
{
    Matrix answer{A.getRowCount(), A.getColumnCount()};
    for(size_t i{0}; i < answer.m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < answer.m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) = A.m_matrix.at(i).at(j) * a;
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

    Matrix answer{A.getRowCount(), A.getColumnCount()};
    for(size_t i{0}; i < answer.m_matrix.size(); ++i)
    {
        for(size_t j{0}; j < answer.m_matrix.at(0).size(); ++j)
        {
            answer.m_matrix.at(i).at(j) = A.m_matrix.at(i).at(j) + B.m_matrix.at(i).at(j);
        }
    }

    return answer;
}
