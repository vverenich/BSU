#ifndef MYCLASS_H7
#define MYCLASS_H7

#include "SoftDrink.h"
#include<string>

enum class Type {
	Citro,
	CreamSoda,
	Duchess,
	Buratino,
	Baikal,
	Tarhun,
};

class Lemonade : public SoftDrink {
private:
	Type type;
public:
	Lemonade(std::string nam, double volum, Type t);
	std::string GetType() const;
	void SetType(Type t);
};

#endif