#include<iostream>
bool prime(int number);
int main()
{
	int N;
	std::cout << "Enter N(N - natural number): ";
	std::cin >> N;
	//all prime numbers can be represented as 6k+1 or 6k-1,k - natural number(except of pair 2,3)
	//so the first pair is (3,5)
	if (N == 1)
	{
	    std::cout << "\nThe first pair of prime numbers: ";
		std::cout << "\n3, 5";
	}

	else 
	{
		std::cout << "\nThe first " << N << " pairs of prime numbers:";
		std::cout << "\n3, 5";
		int k = 0;
		N -= 1;
		while (N != 0)
		{
			++k;
			if (prime(6 * k + 1) && prime(6 * k - 1))
			{
				std::cout << "\n" << 6 * k - 1 << ", " << 6 * k + 1;
				N -= 1;
			}
		}
	}
   
	 
	return 0;
}
bool prime(int number)
{ 
	int dividers = 0;
	int i = 2;
	while ((dividers == 0) && (i <= sqrt(number)))
	{
		if (number % i == 0)
		{
			dividers += 1;
		}
		++i;
	}
	
	if (dividers != 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}