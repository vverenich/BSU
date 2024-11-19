#include "AlcoholicDrink.h"
#include<exception>

double AlcoholicDrink::GetStrength() const
{
	return strength;
}

void AlcoholicDrink::SetStrength(double streng)
{
	if (streng <= 0 || streng > 100) {
		throw std::runtime_error("Strength belongs to the interval (0, 100]");
	}
	else {
		strength = streng;
	}
}
