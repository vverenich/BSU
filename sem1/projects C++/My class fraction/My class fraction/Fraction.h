#ifndef MY_CLASS
#define MY_CLASS

#include <iostream>

class Fraction {
private:
	long numerator;
	long denominator;
	void Reduction();
public:
	Fraction(long num, long den);
	long GetNumerator() const;
	long GetDenominator() const;
	void SetNumerator(long num);
	void SetDenominator(long den);

	Fraction operator +(const Fraction&) const;// const запрещает изменять левый объект
	Fraction operator -(const Fraction&) const;
	Fraction operator *(const Fraction&) const;
	Fraction operator /(const Fraction&) const;
	Fraction operator -() const;

	friend Fraction operator +(const int&, const Fraction&);
	friend Fraction operator -(const int&, const Fraction&);
	friend Fraction operator *(const int&, const Fraction&);
	friend Fraction operator /(const int&, const Fraction&);

	friend Fraction operator +(const Fraction&, const int&);
	friend Fraction operator -(const Fraction&, const int&);
	friend Fraction operator *(const Fraction&, const int&);
	friend Fraction operator /(const Fraction&, const int&);

	bool operator >(const Fraction&) const;
	bool operator <(const Fraction&) const;
	bool operator >=(const Fraction&) const;
	bool operator <=(const Fraction&) const;
	bool operator ==(const Fraction&) const;
	bool operator !=(const Fraction&) const;

	friend bool operator >(const int&, const Fraction&);
	friend bool operator <(const int&, const Fraction&);
	friend bool operator >=(const int&, const Fraction&);
	friend bool operator <=(const int&, const Fraction&);
	friend bool operator ==(const int&, const Fraction&);
	friend bool operator !=(const int&, const Fraction&);

	friend bool operator >(const Fraction&, const int&);
	friend bool operator <(const Fraction&, const int&);
	friend bool operator >=(const Fraction&, const int&);
	friend bool operator <=(const Fraction&, const int&);
	friend bool operator ==(const Fraction&, const int&);
	friend bool operator !=(const Fraction&, const int&);

	double GetDouble();
};

#endif