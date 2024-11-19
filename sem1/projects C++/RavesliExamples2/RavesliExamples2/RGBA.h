#ifndef RGBA_H
#define RGBA_H

#include<cstdint>
#include<iostream>

class RGBA {
	std::uint8_t m_red;
	std::uint8_t m_green;
	std::uint8_t m_blue;
	std::uint8_t m_alpha;

public:
	RGBA(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0,
		std::uint8_t alpha = 0) : m_red(red), m_alpha(alpha), m_blue(blue), m_green(green) {};
	void print() {
		std::cout << "r=" <<(int)m_red << " g=" << (int)m_green << " b=" << (int)m_blue << " a=" << (int)m_alpha;
	}

};

#endif 
