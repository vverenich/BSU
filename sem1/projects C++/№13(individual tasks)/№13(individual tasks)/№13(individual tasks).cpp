#include<iostream>
int main()
{
	int A;
	std::cout << "Enter six-digital number: ";
	std::cin >> A;
	int B = 0;
	
	for (int i = 100; i <= 1000000; i *= 100)
	{
		 
		B = ((((A % i) / (i / 100)) % 10) * 10 + (((A % i) / (i / 100)) / 10)) * (i / 100) + B;
	}

	std::cout <<"\n"<< B;
	return 0;
}