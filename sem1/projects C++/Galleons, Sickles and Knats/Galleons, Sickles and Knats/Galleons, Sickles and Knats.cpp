#include <iostream>
#include <fstream>
#include <exception>

class Balance {
private:
	bool sign;
	long long Galleons;
	long long Sickles;
	long long Knats;
public:
	Balance(bool s, long long gall, long long sick, long long knat) {
		SetGalleons(gall);
		SetSickles(sick);
		SetKnats(knat);
		sign = s;
	}

	Balance() :sign(true), Galleons(0), Sickles(0), Knats(0) {};

	bool GetSign() const {
		if (sign == true) {
			return true;
		}
		else {
			return false;
		}
	}

	long long GetGalleons() const {
		return Galleons;
	}

	long long GetSickles() const {
		return Sickles;
	}

	long long GetKnats() const {
		return Knats;
	}

	void SetGalleons(long long gall) {
		Galleons = gall;
	}

	void SetSickles(long long sick) {
		if (sick > 16 || sick < 0) {
			throw std::runtime_error("wrong value");
		}
		else {
			Sickles = sick;
		}
	}

	void SetKnats(long long knat) {
		if (knat > 28 || knat < 0) {
			throw std::runtime_error("wrong value");
		}
		else {
			Knats = knat;
		}
	}

	friend Balance operator -(const Balance& b1, const Balance& b2) {
		long long inKnats1 = b1.Galleons * 17 * 29 + b1.Sickles * 29 + b1.Knats;
		long long inKnats2 = b2.Galleons * 17 * 29 + b2.Sickles * 29 + b2.Knats;
		if (!b1.GetSign()) {
			inKnats1 *= -1;
		}
		if (!b2.GetSign()) {
			inKnats2 *= -1;
		}
		long long res = inKnats1 - inKnats2;
		bool s;
		if (res < 0) {
			s = false;
		}
		else {
			s = true;
		}
		res = std::abs(res);
	    long long gall = res / (17 * 29);
		res = res - gall * 17 * 29;
		long long sick = res / 29;
		res = res - sick * 29;
		long long knat = res;
		return Balance(s, gall, sick, knat);
	}
};

int main() {
	std::ifstream fin("money.in.txt");
	std::ofstream fout("money.out.txt");
	Balance money;
	long long gall;
	fin >> gall;
	money.SetGalleons(gall);
	long long sick;
	fin >> sick;
	money.SetSickles(sick);
	long long knat;
	fin >> knat;
	money.SetKnats(knat);
	int N;
	fin >> N;
	Balance money2;
	for (int i = 0; i < N; ++i) {
		fin >> gall;
		money2.SetGalleons(gall);
		fin >> sick;
		money2.SetSickles(sick);
		fin >> knat;
		money2.SetKnats(knat);
		money = money - money2;
	}
	if (money.GetSign()) {
		fout << money.GetGalleons() << " " << money.GetSickles() << " " << money.GetKnats();
	}
	else {
		fout << "-1";
	}
	return 0;
}
