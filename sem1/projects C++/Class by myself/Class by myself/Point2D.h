#include<iostream>
#include<ostream>
#include<cmath>
#include<ostream>

#pragma once
class Point2D
{
protected:
	double x, y;
public:
	Point2D();
	Point2D(double , double );
	double GetX() const;
	double GetY() const;
	void SetX(double ax);
	void SetY(double ay);
    double GetPhi() const;
    double GetRo() const;
    Point2D operator-() const;
    Point2D operator++();
    Point2D& operator++(int);
    Point2D operator+(const Point2D ) const;
    bool operator==(const Point2D&);
    bool operator!=(const Point2D&);//how to compare
    Point2D operator*(double) const;//умножение на скал€р
    double operator*(const Point2D&);//скал€рное произведение
    friend Point2D operator*(double, const Point2D& p);
    friend std::ostream& operator<<(std::ostream&, const Point2D&);

};

