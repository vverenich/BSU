#include<iostream>

int binarySearch2(int arr[], int left, int right, int x, int& lastIndex) {
	while (left <= right) {
		int middle = left + (right - left) / 2;
		lastIndex = middle;

		if (arr[middle] == x) {
			return middle;
		}
		else if (x < arr[middle]) {
			right = middle - 1;
		}
		else {
			left = middle + 1;
		}
	}
	return -1;
}
int lowerBound(int arr[], int left, int right, int x) {
	while (left < right) {
		int middle = left + (right - left) / 2;

		if (x <= arr[middle]) {
			right = middle;
		}
		else {
			left = middle + 1;
		}
	}
	return left;
}

int upperBound(int arr[], int left, int right, int x) {
	while (left < right) {
		int middle = left + (right - left) / 2;

		if (x >= arr[middle]) {
			left = middle+1;
		}
		else {
			right = middle;
		}
	}
	return right;
}


int main() {

	int n, k;
	std::cin >> n;
	int* arrayOfNumbers = new int[n];
	for (size_t i{ 0 }; i < n; ++i) {
		scanf("%d", &arrayOfNumbers[i]);
	}
	std::cin >> k;
	int* arrayOfQueries = new int[k];
	for (size_t i{ 0 }; i < k; ++i) {
		scanf("%d", &arrayOfQueries[i]);
	}


	for (size_t i{ 0 }; i < k; ++i) {
		int lastIndex;
		int index = binarySearch2(arrayOfNumbers, 0, n - 1, arrayOfQueries[i], lastIndex);
		if (index != -1) {
			printf("1 ");

			int indexMoreOrEqualTo = lowerBound(arrayOfNumbers, 0, index, arrayOfQueries[i]);
			printf("%d ", indexMoreOrEqualTo );
			
			int indexMore = upperBound(arrayOfNumbers, index, n, arrayOfQueries[i]);
			printf("%d", indexMore);
		}
		else {
			printf("0 ");
			if (arrayOfQueries[i] > arrayOfNumbers[lastIndex]) {
				printf("%d %d", lastIndex + 1, lastIndex + 1);
			}
			else {
				printf("%d %d", lastIndex, lastIndex);
			}
		}
		printf("\n");
	}

	delete[] arrayOfNumbers;
	delete[] arrayOfQueries;

}