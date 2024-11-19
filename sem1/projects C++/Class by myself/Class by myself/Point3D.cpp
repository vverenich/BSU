
#include "Point3D.h"

double Point3D::getZ() const
{
	return z;
}

void Point3D::setZ(double p)
{
	z = p;
}

Point3D::Point3D(double aX, double aY, double aZ) :Point2D(aX, aY)
{
	setZ(aZ);
}
