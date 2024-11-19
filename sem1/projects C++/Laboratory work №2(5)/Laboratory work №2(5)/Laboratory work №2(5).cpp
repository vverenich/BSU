#include<iostream>
#include<ctime>
#include<random>
int main()
{
	double s,x, res, beg;
	int a, n;
	std::cout << "Enter operational margin: ";
	std::cin >> s;
	std::cout << "\nEnter alpha: ";
	std::cin >> a;

	std::default_random_engine generator(time(0));
	std::uniform_real_distribution<float> distribution(-1, 1);
	x = distribution(generator);

	std::cout << "\nRandom number x: " << x;
	beg = 1;
	res = 1;
	n = 0;
	do
	{
		++n;
		beg = beg * (a - n + 1)*x / n;
		res = res + beg;

	} while (s < abs(beg-(beg*n/(x*(a-n+1)))));

	std::cout << "\nResults: (1+x)^a = " << pow(1 + x, a) << ", our value = " << res;
	return 0;
}