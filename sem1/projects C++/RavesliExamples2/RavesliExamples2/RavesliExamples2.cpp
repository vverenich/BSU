
#include"Point.h"

class Base
{
public:
	virtual void function1() {};
	virtual void function2() {};
};

class D1 : public Base
{
public:
	virtual void function1() {};
};

class D2 : public Base
{
public:
	virtual void function2() {};
};
int main()
{

	D1 d1;
	Base *dPtr = &d1;
	dPtr->function2();
}