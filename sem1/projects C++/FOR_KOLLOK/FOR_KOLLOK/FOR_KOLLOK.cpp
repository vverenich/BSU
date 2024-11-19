 

#include <iostream>

int main()
{
    const double PI = 3.14159265358;
    int r, h;

    std::cin >> r >> h;
    std::cout << std::sqrt(r * r + h * h) * r * PI;
}