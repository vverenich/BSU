#include<iostream>
#include<ctime>
#include<random>
int main()
{
	float x, s;
	std::cout << "Enter operational margin s : ";
	std::cin >> s;

	std::default_random_engine generator(time(0));
	std::uniform_real_distribution<float> distribution(-85, 709);//pow(e,709) is very big number,so this function return inf 
	x = distribution(generator);

	std::cout << "\nRandom number x : " << x << std::endl;
	const float e = 2.718281828;
	int n = 0;
	double beg = 1;
	double res = 0;
	do
	{
		++n;
		res = res + beg;
		beg = beg * x / n;
	} while (abs(beg-(beg*n/x)) > s);

	std::cout << "\ne^x = " <<  exp(x) << ", our value: " << res << std::endl;
	return 0;
}