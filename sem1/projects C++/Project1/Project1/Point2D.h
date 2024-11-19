#include <iostream>

#pragma once
class Point2D
{
private:
	double x, y;

public:
	double getX();
	void setX(double) const;
	double getY();
	void setY(double) const ;
	double getRo();
	double getPhi();
	Point2D(double = 1,double = 2);
	virtual ~Point2D(void);
};

