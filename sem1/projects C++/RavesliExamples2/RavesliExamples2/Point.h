#ifndef POINT_H
#define POINT_H

#include<iostream>
#include<cmath>


class Point
{
private:
	double m_a, m_b;
public:
	Point(double a = 0.0, double b = 0.0):m_a(a), m_b(b){}
	void print() const {
		std::cout << "\nPoint(" << m_a << ", " << m_b << ")";
	}
	friend double distanceTo(const Point p1, const Point &p2);
};
double distanceTo(const Point p1, const Point &p2) {
	return sqrt((p1.m_a - p2.m_a) * (p1.m_a - p2.m_a) + (p1.m_b - p2.m_b) * (p1.m_b - p2.m_b));
}


#endif 