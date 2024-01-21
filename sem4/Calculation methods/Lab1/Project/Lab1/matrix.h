#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cmath>

class Matrix
{
private:
    std::vector<std::vector<double>> m_matrix;
public:
    Matrix() noexcept;
    Matrix(const unsigned, const unsigned) noexcept;
    Matrix(const std::vector<std::vector<double>> &matrix);

    unsigned getColumnCount() const;
    unsigned getRowCount() const;

    void setMatrixElement(const unsigned, const unsigned, const double);
    double getMatrixElement(const unsigned, const unsigned) const;

    Matrix getTransposedMatrix() const;
    static Matrix getIdentityMatrix(const size_t, const size_t);
    double getNorm3() const;
    void getLUPdecomp(Matrix &L, Matrix &U, Matrix &P) const;
    void getLDLtransposedDecomp(Matrix &L, Matrix &D, Matrix &Ltransposed) const;
    void swapColumns(const size_t colIndex1, const size_t colIndex2);
    void swapRows(const size_t rowIndex1, const size_t rowIndex2);

    friend bool operator==(const Matrix&, const Matrix&);
    friend std::ostream& operator<<(std::ostream &, const Matrix &);
    Matrix operator*(const Matrix&);
    friend Matrix operator*(double a, const Matrix &);
    friend Matrix operator+(const Matrix &, const Matrix &);
    Matrix operator-() const;
};

Matrix operator+(const Matrix &, const Matrix &);
Matrix operator*(double a, const Matrix &);
bool operator==(const Matrix&, const Matrix&);
std::ostream& operator<<(std::ostream &, const Matrix &);

#endif // MATRIX_H
