#pragma once
class Balance
{
private:
	bool sign;
	long long pound;
	long long shilling;
	double pence;
public:
	Balance(bool s, long long pd, long long sh, double p);
	Balance(long long pd, long long sh, double p);
	Balance() :pound(0), shilling(0), pence(0), sign(true) {};
	void GetBalance();
	friend Balance operator +(const Balance& b1, const Balance& b2);
	friend Balance operator -(const Balance& b1, const Balance& b2);
	Balance& operator -();
	friend Balance operator +=(Balance& b1, const Balance& b2);
	friend Balance operator -=(Balance& b1, const Balance& b2);
	friend bool operator >(const Balance& b1, const Balance& b2);
	friend bool operator <(const Balance& b1, const Balance& b2);
	friend bool operator >=(const Balance& b1, const Balance& b2);
	friend bool operator <=(const Balance& b1, const Balance& b2);
	friend bool operator !=(const Balance& b1, const Balance& b2);
	friend bool operator ==(const Balance& b1, const Balance& b2);
};

