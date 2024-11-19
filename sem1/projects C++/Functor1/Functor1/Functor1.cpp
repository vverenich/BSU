#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

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
		return s.size() - 1 - i;
	}
    bool operator()(double n1, double n2) {
		std::string str1 = std::to_string(n1);
		std::string str2 = std::to_string(n2);
		return NumberOfSignificantDigitals(str2) > NumberOfSignificantDigitals(str2);
	}
};

int main() {
	std::ifstream fin("IN.txt");
	std::ofstream fout("OUT.txt");
	if (!fin.is_open()) {
		throw std::exception("Error opening file.");
	}
	try {
		if (fin.peek() == std::ifstream::traits_type::eof())
			throw eceprtion()
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what();
	}
	/*{
		fout << "File is empty.";
		return 0;
	}*/
	std::vector<double> Numbers;
	while (!fin.eof()) {
		double num;
		fin >> num;
		Numbers.push_back(num);
	}
	for (int i = 0; i < Numbers.size(); ++i) {
		fout << Numbers[i] << "\n";
	}
	std::sort(Numbers.begin(), Numbers.end(), Sorter());
	for (int i = 0; i < Numbers.size(); ++i) {
		fout << Numbers[i] << "\n";
	}

	return 0;
}