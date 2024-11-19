#ifndef MYCLASS_H4
#define MYCLASS_H4

#include "AlcoholicDrink.h"
#include<string>

enum class Grape {
	UnyBlanc,
	FoilBlanche,
	Colombard,
	Montil,
	JurensonBlanc,
	Semillon,
};

class Cognac : public AlcoholicDrink {
private:
	Grape grape;
public:
	Cognac(std::string nam, double volum, double streng, Grape g);
	std::string GetGrape() const;
	void SetGrape(Grape g);
};

#endif