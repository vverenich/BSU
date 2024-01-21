#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
int main() {
	std::ofstream fout("output.txt");
	std::ifstream fin("input.txt");

	int n;
	fin >> n;
	int* arr = new int[n+1];
	for (int i{ 0 }; i < n; ++i) {
		fin >> arr[i+1];
	}
	std::string answer;
	for (int i{ 1 }; i <= n; ++i) {
		if (2 * i + 1 <= n) {
			if (arr[i] > arr[2 * i + 1] ||arr[i]>arr[2*i]) {
				answer = "No";
				break;
			}
			continue;
		}
		else if (2 * i <= n) {
			if (arr[i] > arr[2 * i]) {
				answer = "No";
				break;
			}
			continue;
		}
		else {
			answer = "Yes";
		}
	}

	fout <<answer;
	delete[] arr;
}