#include <iostream>
#include "Point2D.h"

int main() {
	Point2D p(3, 5);
	std::cout << p.getX() << "\n" << p.getY() << std::endl;
	try {
		std::cout << p.getPhi() << std::endl;
	}
	catch (...) {
		std::cout << "Impossible to colculate polar radius in this case!";
	}
	return 0;
}