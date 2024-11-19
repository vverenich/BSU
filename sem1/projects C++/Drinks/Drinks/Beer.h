#ifndef MYCLASS_H3
#define MYCLASS_H3

#include "AlcoholicDrink.h"
#include<string>

enum class Raw {
	barley,
	wheat,
	ginger
};

class Beer : public AlcoholicDrink {
private:
	Raw typeOfRaw;
public:
	Beer(std::string nam, double volum, double streng, Raw r);
	std::string GetTypeRaw() const;
	void SetTypeRaw(Raw r);
};

#endif