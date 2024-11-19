#include<iostream>

#pragma once
class verchik
{
private:
	double x, y;

public:
	double getX();
	void setX(double) const;
	double getY();
	void setY(double) const;
	double getRo();
	double getPhi();
	verchik(double = 1, double = 2);
	virtual ~verchik(void);
};


