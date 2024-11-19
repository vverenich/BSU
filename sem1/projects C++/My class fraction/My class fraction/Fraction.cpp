#include "Fraction.h"
#include <cmath>

void Fraction::Reduction()
{
	if (numerator == 0) {
		denominator = 1;
	}
	else {
		long den1 = std::abs(denominator);
		long num1 = std::abs(numerator);
		while (den1 != 0 && num1 != 0) {
			if (den1 > num1) {
				den1 = den1 % num1;
			}
			else {
				num1 = num1 % den1;
			}
		}
		numerator /= den1 + num1;
		denominator /= den1 + num1;
		if (denominator < 0) {
			numerator *= -1;
			denominator *= -1;
		}
	}
}

Fraction::Fraction(long num, long den)
{
	if (den == 0) {
		throw std::runtime_error("denominator can not be zero");
	}
	numerator = num;
	denominator = den;
	Reduction();

}

long Fraction::GetNumerator() const
{
	return numerator;
}

long Fraction::GetDenominator() const
{
	return denominator;
}

void Fraction::SetNumerator(long num)
{
	numerator = num;
	Reduction();
}

void Fraction::SetDenominator(long den)
{
	denominator = den;
	Reduction();
	if (den == 0) {
		throw std::runtime_error("denominator can not be zero");
	}

}

Fraction Fraction::operator +(const Fraction& f) const
{
	long num = this->numerator * f.denominator + this->denominator * f.numerator;
    long den = this->denominator * f.denominator;
	return Fraction(num, den);
}

Fraction Fraction::operator -(const Fraction& f) const
{
	long num = this->numerator * f.denominator - this->denominator * f.numerator;
	long den = this->denominator * f.denominator;
	return Fraction(num, den);
}

Fraction Fraction::operator *(const Fraction& f) const
{
	long num = this->numerator * f.numerator;
	long den = this->denominator * f.denominator;
	return Fraction(num, den);
}

Fraction Fraction::operator /(const Fraction& f) const
{
	long num = this->numerator * f.denominator;
	long den = this->denominator * f.numerator;
	return Fraction(num, den);
}

Fraction Fraction::operator -() const
{
	return Fraction(-numerator, denominator);
}

bool Fraction::operator >(const Fraction& f) const
{
	if (this->numerator * f.denominator > f.numerator * this->denominator) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator <(const Fraction& f) const
{
	if (this->numerator * f.denominator < f.numerator * this->denominator) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator >=(const Fraction& f) const
{
	if (*this > f || *this == f) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator <=(const Fraction& f) const
{
	if (*this == f || *this < f) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator ==(const Fraction& f) const
{
	if (this->numerator * f.denominator == f.numerator * this->denominator) {
		return true;
	}
	else {
		return false;
	}
}

bool Fraction::operator!=(const Fraction& f) const
{
	if (!(*this == f)) {
		return true;
	}
	else {
		return false;
	}
}

double Fraction::GetDouble()
{
	return(static_cast<double>(numerator) / denominator);
}

Fraction operator +(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	return f1 + (f2);
}

Fraction operator -(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	return f1 - (f2);
}

Fraction operator *(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	return f1 * (f2);
}

Fraction operator /(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	return f1 / (f2);
}

Fraction operator +(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	return f1 + (f2);
}

Fraction operator -(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	return f1 - (f2);
}

Fraction operator *(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	return f1 * (f2);
}

Fraction operator /(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	return f1 * (f2);
}

bool operator >(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator > f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator <(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator < f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator >=(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator >= f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator <=(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator <= f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator !=(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator != f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator ==(const int& a, const Fraction& f2)
{
	Fraction f1(a, 1);
	if (f1.numerator * f2.denominator == f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator >(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator > f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator <(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator < f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator >=(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator >= f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator <=(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator <= f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator !=(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator != f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}

bool operator ==(const Fraction& f1, const int& a)
{
	Fraction f2(a, 1);
	if (f1.numerator * f2.denominator > f1.denominator * f2.numerator) {
		return true;
	}
	else {
		return false;
	}
}