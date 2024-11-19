#include "Point2D.h"
#define PI std::acos(-1)

Point2D::Point2D()
{
    x = 0; y = 0;
}

Point2D::Point2D(double ax, double ay) : x(ax), y(ay) {}

double Point2D::GetX() const
{
    return x;
}

double Point2D::GetY() const
{
    return y;
}

void Point2D::SetX(double ax)
{
    x = ax;
}

void Point2D::SetY(double ay) 
{ 
    y = ay; 
}

double Point2D::GetPhi() const 
{
  if (x == 0 && y == 0) {
    throw std::exception("This point is a pole");
  }
  if (x > 0 && y > 0) {
    return std::atan(y / x);
  }
  if (x == 0 && y > 0) {
    return PI/2;
  }
  if (x < 0 && y > 0) {
    return PI + std::atan(y / x);
  }
  if (x < 0 && y == 0) {
    return PI;
  }
  if (x < 0 && y < 0) {
    return -PI + std::atan(y / x);
  }
  if (x == 0 && y < 0) {
    return -PI / 2;
  }
  if (x > 0 && y < 0) {
    return std::atan(y/x);
  }
  }

double Point2D::GetRo() const 
{ 
    return std::sqrt(x*x+y*y); }

 Point2D Point2D::operator -() const
 { 
     return Point2D(-x,-y);
 }


Point2D Point2D::operator++() 
{
    y++;
    x++;
    return *this;
}

Point2D& Point2D::operator++(int) 
{
    Point2D p (*this);
    x++;y++;
    return p;
}

Point2D Point2D::operator+(const Point2D other) const
{ 
    return Point2D(this->x + other.x, this->y + other.y);
}

bool Point2D::operator==(const Point2D& p) 
{ 
    return this->x == p.x && this->y == p.x;
}

bool Point2D::operator!=(const Point2D& p) 
{ 
    return (! this->operator ==(p) ); }

Point2D Point2D::operator*(double d) const 
{ 
    return Point2D(x*d,y*d);
}

double Point2D::operator*(const Point2D& p) 
{ 
    return (this->GetRo() * p.GetRo() * std::acos(std::abs(this->GetPhi() - p.GetPhi())));

}
 
Point2D operator*(double d, const Point2D& p) 
{ 
    return p.operator*(d); }

std::ostream& operator<<(std::ostream& s, const Point2D& p)
{
  s << "(" << p.x << "," << p.y << ")";
  return s;
}
