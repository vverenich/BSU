#include"Balance.h"
#include<iostream>
#include<cmath>

Balance::Balance(bool s, long long pd, long long sh, double p)
{
	if (pd >= 1000000000) {
		pound = 1000000000;
		shilling = 0;
		pence = 0;
	}
	else {
		pound = pd;
		shilling = sh;
		pence = p;
	}
	sign = s;
}

Balance::Balance(long long pd, long long sh, double p)
{
	if (pd < 0 || (sh < 0 || sh >= 20) || (p < 0 || p >= 12 || p - long long(p) != 0.5 && p - long long(p) != 0)) {
		throw std::invalid_argument("Wrong parameter");
	}
	else {
		if (pd >= 1000000000) {
			pound = 1000000000;
			shilling = 0;
			pence = 0;
		}
		else {
			pound = pd;
			shilling = sh;
			pence = p;
		}
		sign = true;
	}
}

void Balance::GetBalance()
{
	if (!sign) {
		std::cout << "-";
	}
	if (pound != 0) {
		std::cout << pound << "pd.";
	}
	if (shilling != 0) {
		std::cout << shilling << "sh.";
	}
	if ((shilling == 0 && pound == 0 && pence == 0) || (pence != 0)) {
		std::cout << pence << "p.";
	}
}

Balance& Balance::operator-()
{
	double in_pence = double(this->pound) * 20 * 12 + double(this->shilling) * 12 + this->pence;
	if (in_pence != 0) {
		sign = !sign;
	}
	return *this;
}

Balance operator+(const Balance& b1, const Balance& b2)
{
	double pence1 = double(b1.pound) * 20 * 12 + double(b1.shilling) * 12 + b1.pence;
	double pence2 = double(b2.pound) * 20 * 12 + double(b2.shilling) * 12 + b2.pence;
	if (!b1.sign) {
		pence1 *= -1;
	}
	if (!b2.sign) {
		pence2 *= -1;
	}

	double pence3 = pence1 + pence2;
	bool sign_;
	if (pence3 < 0) {
		sign_ = false;
	}
	else {
		sign_ = true;
	}
	pence3 = std::abs(pence3);
	long long pound_ = pence3 / 240;
	pence3 -= double(pound_ * 12 * 20);
	long long shilling_ = pence3 / 12;
	pence3 -= double(shilling_ * 12);
	double pence_ = pence3;
	return Balance(sign_, pound_, shilling_, pence_);
}

Balance operator-(const Balance& b1, const Balance& b2)
{
	double pence1 = double(b1.pound) * 20 * 12 + double(b1.shilling) * 12 + b1.pence;
	double pence2 = double(b2.pound) * 20 * 12 + double(b2.shilling) * 12 + b2.pence;
	if (!b1.sign) {
		pence1 *= -1;
	}
	if (!b2.sign) {
		pence2 *= -1;
	}

	double pence3 = pence1 - pence2;
	bool sign_;
	if (pence3 < 0) {
		sign_ = false;
	}
	else {
		sign_ = true;
	}
	pence3 = std::abs(pence3);
	long long pound_ = pence3 / 240;
	pence3 -= double(pound_ * 12 * 20);
	long long shilling_ = pence3 / 12;
	pence3 -= double(shilling_ * 12);
	double pence_ = pence3;
	return Balance(sign_, pound_, shilling_, pence_);
}

Balance operator+=(Balance& b1, const Balance& b2)
{
	b1 = b1 + b2;
	return b1;
}

Balance operator-=(Balance& b1, const Balance& b2)
{
	b1 = b1 - b2;
	return b1;
}

bool operator>(const Balance& b1, const Balance& b2)
{
	double pence1 = double(b1.pound) * 20 * 12 + double(b1.shilling) * 12 + b1.pence;
	double pence2 = double(b2.pound) * 20 * 12 + double(b2.shilling) * 12 + b2.pence;
	if (!b1.sign) {
		pence1 *= -1;
	}
	if (!b2.sign) {
		pence2 *= -1;
	}
	if (pence1 > pence2) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const Balance& b1, const Balance& b2)
{
	if (b1 >= b2) {
		return false;
	}
	else {
		return true;
	}
}

bool operator>=(const Balance& b1, const Balance& b2)
{
	double pence1 = double(b1.pound) * 20 * 12 + double(b1.shilling) * 12 + b1.pence;
	double pence2 = double(b2.pound) * 20 * 12 + double(b2.shilling) * 12 + b2.pence;
	if (!b1.sign) {
		pence1 *= -1;
	}
	if (!b2.sign) {
		pence2 *= -1;
	}
	if (pence1 >= pence2) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<=(const Balance& b1, const Balance& b2)
{
	if (b1 > b2) {
		return false;
	}
	else {
		return true;
	}
}

bool operator!=(const Balance& b1, const Balance& b2)
{
	if (b1 == b2) {
		return false;
	}
	else {
		return true;
	}
}

bool operator==(const Balance& b1, const Balance& b2)
{
	double pence1 = double(b1.pound) * 20 * 12 + double(b1.shilling) * 12 + b1.pence;
	double pence2 = double(b2.pound) * 20 * 12 + double(b2.shilling) * 12 + b2.pence;
	if (!b1.sign) {
		pence1 *= -1;
	}
	if (!b2.sign) {
		pence2 *= -1;
	}
	if (pence1 == pence2) {
		return true;
	}
	else {
		return false;
	}
}
