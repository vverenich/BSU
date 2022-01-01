#include<iostream>
#include<fstream>
#include<algorithm>

int findMax(int arr[], int size) {
	if (size == 1) {
		return arr[0];
	}
	if (size == 2) {
		return -1;
	}
	arr[1] = -1;
	for (int i{ 2 }; i < size; ++i) {
		int value1 = 0;
		int value2 = 0;
		if (i - 2 >= 0 && arr[i-2]!=-1) {
			value1 = arr[i - 2];
		}
		if (i - 3 >= 0 && arr[i - 3] != -1) {
			value2 = arr[i - 3];
		}
		arr[i] = std::max(value1, value2) + arr[i];
	}
	return arr[size - 1];
}
int main() {
	std::ofstream fout("output.txt");
	std::ifstream fin("input.txt");

	
	int n;
	fin >> n;
	int *arr = new int[n];
	for (size_t i{ 0 }; i < n; ++i) {
		fin >> arr[i];
	}

	fout<<findMax(arr, n);

	delete[] arr;
}