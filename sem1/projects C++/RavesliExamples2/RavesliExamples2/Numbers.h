#ifndef CLASS_NUMBERS
#define CLASS_NUMBERS

#include<iostream>

class Numbers
{
    double m_a;
	double m_b;
	double m_c;

public:
	void setValues(int a, int b, int c) {
		m_a = a;
		m_b = b;
		m_c = c;
	}
	void print() {
		std::cout << "<" << m_a << ", " << m_b <<", "<<m_c<< ">";
	}
	bool isEqual(const Numbers &number) {
		return (m_a == number.m_a && m_b == number.m_b && m_c == number.m_c);
		
	}
};

#endif

