#ifndef MYCLASS_H6
#define MYCLASS_H6

#include "SoftDrink.h"
#include<string>

enum class Kind
{
	Bicarbonate,
	Sulfate,
	Chloride,
	Calcium,
	Magnesium,
	Sodium,
	Sour,
	Glandular,
	Fluorine,
};

class MineralWater : public SoftDrink {
private:
	Kind kind;
public:
	MineralWater(std::string nam, double volum, Kind k);
	std::string GetKind() const;
	void SetKind(Kind k);
};

#endif