#include <iostream>
#include<ostream>
#include"Point2D.h"

void PrintPoint(const Point2D& p) {
    std::cout << p.GetX() << " " << p.GetY() << "\n";
    std::cout<<p.GetRo()<< std::endl;
}

void my_func() {
    Point2D p1;
    Point2D* t1 = new Point2D(10, -3);
    Point2D* t2 = new Point2D(0, 16);
    delete t1;
    delete t2;
}
int main()
{
  Point2D p(3,4);
  Point2D p1(1, 1);
  PrintPoint(p);
  p=-(p);//унарный минус
  PrintPoint(p);
  p = ++(p);//инкремент
  PrintPoint(p);
  p = -(p);
  p = ++(p);
  PrintPoint(p);
  p=p +(p1);//.бинарная операция сложения
  PrintPoint(p);
  p = p * (3);  // умножение на скаляр
  PrintPoint(p);
  
  return 0;
}

 