#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

struct Cell {
	int number;
	Cell *ptr;
	char symbol;
};

std::string getPalindrome(const std::string &str) {
	int n = str.length();

	Cell **table = new Cell * [n];
	for (int i{ 0 }; i < n; ++i) {
		table[i] = new Cell[n];
	}

	for (int i{ 0 }; i < n; ++i) {
		table[i][i].number = 1;
		table[i][i].ptr = nullptr;
		table[i][i].symbol = str[i];
	}

	for (int  i{ 1 }; i < n; ++i) {
		if (str[i - 1] == str[i]) {
			table[i - 1][i].number = 2;
		} else {
			table[i - 1][i].number = 1;
		}
		table[i - 1][i].ptr = nullptr;
		table[i - 1][i].symbol = str[i];
	}

	for (int i{ 2 }; i < n; ++i) {
		for (int j{ 0 }; j + i < n; ++j) {
			if (str[j] == str[i + j]) {
				table[j][i + j].number = table[j + 1][i + j - 1].number + 2;
				table[j][i + j].ptr = &table[j + 1][i + j - 1];
				table[j][i + j].symbol = str[i + j];
			} else {
				if (table[j + 1][i + j].number > table[j][i + j - 1].number) {
					table[j][i + j].number = table[j + 1][i + j].number;
					table[j][i + j].ptr = table[j + 1][i + j].ptr;
					table[j][i + j].symbol = table[j + 1][i + j].symbol;
				} else {
					table[j][i + j].number = table[j][i + j - 1].number;
					table[j][i + j].ptr = table[j][i + j - 1].ptr;
					table[j][i + j].symbol = table[j][i + j - 1].symbol;
				}
			}
		}
	}

	std::string result;
	int lastNumber = -1;
	Cell *ptr = &table[0][n - 1];
	while (ptr != nullptr) {
		result += ptr->symbol;
		lastNumber = ptr->number;
		ptr = ptr->ptr;
	}

	int length = result.length();

	if (lastNumber == 2) {
		for (int i = 0; i < length; ++i) {
			result += result[length - 1 - i];
		}
	}
	else {
		for (int i = 1; i < length; ++i) {
			result += result[length - 1 - i];
		}
	}

	for (int i{ 0 }; i < str.length(); ++i) {
		delete[] table[i];
	}

	delete[] table;

	return result;
}

int main() {
	std::ofstream fout("output.txt");
	std::ifstream fin("input.txt");

	std::string str;
	fin>> str;

	std::string result = getPalindrome(str);

	fout<< result.length()<< "\n"<< result;
}
