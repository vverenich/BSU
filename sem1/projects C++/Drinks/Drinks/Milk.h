#ifndef MYCLASS_H5
#define MYCLASS_H5

#include "SoftDrink.h"
#include<string>

class Milk : public SoftDrink {
private:
	double fatContent;
public:
	Milk(std::string nam, double volum, double fatCont);
	double GetFatContent() const;
	void SetFatContent(double fatCont);
};

#endif