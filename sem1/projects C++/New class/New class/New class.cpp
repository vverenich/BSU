#include <iostream>
#include<optional>
#include<utility>
#include<algorithm>
#include<vector>

bool compare(int x, int y) {
	return x < y;
}
int main() {
	std::vector<int> numbers = { 4,2,7,5,8,6,4,3 };
	for (size_t i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i] << " ";
	}
	std::cout << "\n";
	std::sort(numbers.begin(), numbers.end());
	for (size_t i = 0; i < numbers.size(); ++i) {
		std::cout << numbers[i] << " ";
	}


	std::optional<double> numbers2[5] = { 64,26,21, 100 };
	std::cout << numbers2[5];
}
	/*int arr[5] = { 4,5,3,2,1 };
	std::sort(&arr[0], arr[4]);
	std::pair<int, size_t> arr_idx[5];
	for (size_t i = 0; i < 5; ++i) {
		arr_idx[i] = std::make_pair(std::abs(arr_idx[i]), i);
	}
	std::qsort(first:&arr_idx[0], last : &arr_idx[5]);

	int arr2[5];
	for (size_t i = 0; i < 5; ++i) {
		arr2[i] = arr[i];
	}
	for(size_t i = 0; i<5;++i)
	 
		return 0;
}
*/