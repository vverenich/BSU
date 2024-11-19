#ifndef MYCLASS_H
#define MYCLASS_H

#include<iostream>
#include<string>
                               //gproblem of rule of 5
class BottledDrink {
protected:
	std::string name;
	double volume;
public:
	std::string GetName() const;
	double GetVolume() const;
	void SetName(std::string nam);
	void SetVolume(double vol);
	virtual ~BottledDrink() = 0;
};

inline BottledDrink::~BottledDrink() {}

#endif
