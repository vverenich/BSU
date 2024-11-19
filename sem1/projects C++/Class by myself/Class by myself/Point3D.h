#pragma once
#include "Point2D.h"
class Point3D :
    public Point2D
{
private:
    double z;
public:
    double getZ() const;
    void setZ(double);
    Point3D(double, double, double);
    virtual ~Point3d() {};
};
