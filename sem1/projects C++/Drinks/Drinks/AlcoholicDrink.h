#ifndef MYCLASS_H1
#define MYCLASS_H1

#include "BottledDrink.h"

class AlcoholicDrink : public BottledDrink {
protected:
	double strength;
public:
	double GetStrength() const;
	void SetStrength(double streng);
	virtual ~AlcoholicDrink() = 0;
};

inline AlcoholicDrink::~AlcoholicDrink() {};

#endif