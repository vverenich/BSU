#include <iostream>
#include"Balance.h"

int main()
{
	Balance money1;
	-(money1);
	money1.GetBalance();
	std::cout << std::endl;
	Balance money2(999999999, 19, 1.5);
	-(money2);
	money2.GetBalance();
	std::cout << std::endl;
	Balance money3 = money1 - money2;
	money3.GetBalance();
	std::cout << std::endl;
	money2 += money1;
	money2.GetBalance();
	std::cout << std::endl;
	money2 -= money1;
	money2.GetBalance();
	std::cout << std::endl;
	if (money1 <= money3) {
		std::cout << "good";
	}
	else {
		std::cout << "No good";
	}
}
