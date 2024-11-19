#ifndef CLASS_STACK
#define CLASS_STACK

#include<iostream>
#include<cassert>

class Stack
{
	int m_array[10]{0};
	int m_size = 0;
public:
	void reset() {
		for (int i = 0; i < m_size; ++i) {
			m_array[i] = 0;
		}
		m_size = 0;
	}
	bool push(int a) {
		if (m_size == 10) {
			return false;
		} else {
			++m_size;
			m_array[m_size - 1] = a;
			return false;
		}
	}
	void pop() {
		assert(m_size);
		m_array[m_size] = 0;
		--m_size;
	}
	void print() {
		std::cout << "(";
		for (int i = 0; i < m_size; ++i) {
			std::cout << m_array[i];
			if (i != m_size - 1) {
				std::cout<<", ";
			}
		}
		std::cout << ")\n";
	}
};

#endif
