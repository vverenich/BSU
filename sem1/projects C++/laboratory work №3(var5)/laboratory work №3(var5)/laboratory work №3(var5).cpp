#include<iostream>
#include<ctime>
#include<random>
int main()
{
	int N = 0;
	while (N < 1){
		std::cout << "Enter the number of elements(at least 1 element): ";
		std::cin >> N;
		if (N < 1){
			std::cout << "You made an illegal choice.";
		}
	}

	int* array = new int[N];
	int choice = 0;
	while (choice != 1 && choice != 2){
		std::cout << "\nYou can enter all the elements (enter 1) or generate them(enter 2): ";
		std::cin >> choice;
		if (choice != 2 && choice != 1){
			std::cout << "You made an illegal choice.";
		}
	}

	if (choice == 1){
		for (int i = 0; i < N; ++i){
			std::cout << "Enter element number " << i + 1 << " :";
			std::cin >> array[i];
		}
	}

	else{
		std::default_random_engine generator(time(0));
		std::uniform_int_distribution<int> distribution(-100, 100);
		for (int i = 0; i < N; ++i){
			array[i] = distribution(generator);
			std::cout << "\n" << array[i];
		}
	}

	int maxNumber = array[0];
	int max = 0;
	for (int i = 0; i < N; ++i){
		if (maxNumber < array[i]){
			maxNumber = array[i];
			max = i;
		}
	}
	std::cout << "\n1)Maximum element number: " << (max + 1);
	int n1 = -2;
	int n2 = -2;
	for (int i = 0; i < N; ++i){
		if (array[i] == 0 && n1 == -2){
			n1 = i;
		}

		else if (array[i] == 0){
			n2 = i;
		}
	}

	if ((n1 == -2) && (n2 == -2)){
		std::cout << "\n2)There is no null among these elements.";
	}

	if (n1 != -2 && n2 == -2){
		std::cout << "\n2)There is only one null among these elements.";
	}

	if (n2 == n1 + 1){
		std::cout << "\n2)There is no elements between the first null and the second null.";
	}

	if (n1 != -2 && n2 != -2){
		int p = 1;
		for (int i = n1 + 1; i < n2; ++i){
			p *= array[i];
		}

		std::cout << "\n2)Product of elements between the first null and the second null: " << p;
	}


	if (N % 2 == 0){
		for (int i = N - 2, j = N - 3; i >N/2; --i, j -= 2){
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}

	else{
		for (int j = N - 1, i = N - 2; j > (N-1)/2; --j, i -= 2){
			int t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}

	std::cout << "\n3)New array: ";
	for (int i = 0; i < N; ++i){
		std::cout << "\n" << array[i];
	}
	return 0;
}