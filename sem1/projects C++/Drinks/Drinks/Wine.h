#ifndef MYCLASS_H8
#define MYCLASS_H8

#include "AlcoholicDrink.h"
#include<string>

class Wine : public AlcoholicDrink {
private:
	double holdingTime;
public:
	Wine(std::string nam, double volum, double streng, double holdingTim);
	double GetHoldingTime() const;
	void SetHoldingTime(double h);
};

#endif