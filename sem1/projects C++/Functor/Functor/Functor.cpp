#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>

class Sorter {
public:
	int NumberOfSignificantDigitals(std::string s) {
		char a = s[0];
		int i = 0;
		while (a != '.' && i < s.size()) {
			a = s[i];
			++i;
		}
		if (i == s.size()) {
			return 0;
		}
		return s.size() - i;
	}
	bool operator()(double n1, double n2) {
		std::stringstream s1;
		std::stringstream s2;
		s1 << std::setprecision(std::numeric_limits<double>::digits10 + 1) << n1;
		s2 << std::setprecision(std::numeric_limits<double>::digits10 + 1) << n2;
		std::string str1 = s1.str();
		std::string str2 = s2.str();
		return NumberOfSignificantDigitals(str1) < NumberOfSignificantDigitals(str2);
	}
};

std::ostream& PrintOutVector(std::ostream& out, const std::vector<double>& v) {
	for (int i = 0; i < v.size(); ++i) {
		out << std::setprecision(std::numeric_limits<double>::digits10 + 1) << v[i];
		if (i != v.size() - 1) {
			out << "\n";
		}
	}
	return out;
}

int main() {
	std::ifstream fin("IN.txt");
	std::ofstream fout("OUT.txt");
	if (!fin.is_open()) {
		throw std::exception("Error opening file.");
	}
	if (fin.peek() == std::ifstream::traits_type::eof()) {
		fout << "File is empty.";
		return 0;
	}
	std::vector<double> Numbers;
	while (!fin.eof()) {
		double num;
		fin >> num;
		Numbers.push_back(num);
	}
	fout << "Initial vector:\n";
	PrintOutVector(fout, Numbers);
	std::sort(Numbers.begin(), Numbers.end(), Sorter());
	fout << "\nFinal vector:\n";
	PrintOutVector(fout, Numbers);
}
