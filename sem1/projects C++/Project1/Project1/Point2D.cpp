#include "Point2D.h"

double Point2D::getPhi()
{
	return 0.0;
}

Point2D::Point2D(double aX, double aY)
{
	setX(aX);
	setY(aY);
}

std::string toString() {
	return "(";
}


double Point2D::getX() const {
	return x;
}


void Point2D::setX(double aX) {
	x = aX;
}


double Point2D::getY() const {
	return y;
}


void Point2D::setY(double aY) {
	y = aY;
}

double Point2D::getPhi() const {
	if (x == 0 && y == 0) {
		std::cout << "Epic fail!\n";
	}
}


Point2D::~Point2D(void) {

}