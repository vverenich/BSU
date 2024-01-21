#include<iostream>
#include<fstream>
#include<queue>

int  main() {
	std::ifstream fin("huffman.in");
	std::ofstream fout("huffman.out");

	long long  n;
	fin >> n;
	std::priority_queue<long long,std::vector<long long>, std::greater<long long>> queue;

	long long value;
	for (size_t i{ 0 }; i < n; ++i) {
		fin >> value;
		queue.push(value);
	}

	long long result{ 0 };

	while (queue.size() != 1) {
		long long first{ queue.top() };
		queue.pop();
		long long second{ queue.top() };
		queue.pop();

		long long sum{ first + second };
		result += sum;
		queue.push(sum);
	}

	fout << result;
}