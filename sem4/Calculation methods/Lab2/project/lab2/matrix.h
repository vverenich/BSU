#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <complex>


class Matrix
{
private:
    std::vector<std::vector<std::complex<double>>> m_matrix;
public:

    Matrix(const unsigned, const unsigned) noexcept;
    Matrix(const std::vector<std::vector<std::complex<double>>> &matrix);

    Matrix() noexcept;
    Matrix(const Matrix &a) = default;
    Matrix(Matrix &&m);
    Matrix& operator=(Matrix &&a);
    Matrix& operator=(const Matrix &a) = default;

    unsigned getColumnCount() const;
    unsigned getRowCount() const;

    void setMatrixElement(const unsigned, const unsigned, const std::complex<double>);
    std::complex<double> getMatrixElement(const unsigned, const unsigned) const;

    double getNorm3() const;
    double getNorm2() const;
    std::complex<double> getMaxModuloElement();
    void toHessenbergForm();
    std::pair<Matrix, Matrix> QRdecomposition() const;
    std::vector<std::complex<double>> getEigenvaluesQRalgorithm() const;
    static Matrix getRandomMatrix(const size_t, const size_t);
public:
    //
    Matrix getTransposedMatrix() const;
    static Matrix getIdentityMatrix(const size_t, const size_t);
    void getLUPdecomp(Matrix &L, Matrix &U, Matrix &P) const;
    void getLDLtransposedDecomp(Matrix &L, Matrix &D, Matrix &Ltransposed) const;
    void swapColumns(const size_t colIndex1, const size_t colIndex2);
    void swapRows(const size_t rowIndex1, const size_t rowIndex2);
    //


    friend bool operator==(const Matrix&, const Matrix&);
    friend std::ostream& operator<<(std::ostream &, const Matrix &);
    Matrix operator*(const Matrix&) const;
    friend Matrix operator*(std::complex<double> a, const Matrix &);
    friend Matrix operator+(const Matrix &, const Matrix &);
    Matrix operator-() const;
};

Matrix operator+(const Matrix &, const Matrix &);
Matrix operator*(double a, const Matrix &);
bool operator==(const Matrix&, const Matrix&);
std::ostream& operator<<(std::ostream &, const Matrix &);

#endif // MATRIX_H
