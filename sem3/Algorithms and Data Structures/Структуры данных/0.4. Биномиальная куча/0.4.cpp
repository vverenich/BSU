#include<iostream>
#include<vector>
#include<fstream>

void fromDecimalToBinary(long long number, std::vector<bool> &answerOut) {
	int i = 0;
	while (number > 0) {
		answerOut[i] = static_cast<bool>(number % 2);
		number /= 2;
		++i;
	}
}

int  main() {
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");

	long long  N;
	fin >> N;
	std::vector<bool> answer(64, false);

	fromDecimalToBinary(N, answer);

	for (int i{ 0 }; i < answer.size(); ++i) {
		if (answer[i]) {
			fout << i << "\n";
		}
	}
}