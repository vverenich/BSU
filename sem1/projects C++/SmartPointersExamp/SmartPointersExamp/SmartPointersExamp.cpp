

#include <iostream>
#include<memory>
template<int n>
struct {
	enum{ value = };
};
class A {
public:
	A() {
		std::cout << " 1 ";
	}
	A(const A &t) {
		std::cout << " 2 ";
	}
	A &operator=(const A &t) {
		std::cout << " 3 ";
		return *this;
	}
};

int main()
{
	A a1;
	A a2 = a1;
	A a3;
	a3 = a1;
}