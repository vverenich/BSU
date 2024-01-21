#include <iostream>
#include <chrono>
#include <random>
#include <math.h>

#include <QDebug>
#include <QtCharts>

int main()
{
    const double c_D = 3;
    const double c_l = 2;
    const size_t c_N = 1000;
    size_t n         = 0;

    std::mt19937 mt{ static_cast<unsigned int>(
            std::chrono::steady_clock::now().time_since_epoch().count()
            ) };
    std::uniform_real_distribution<> corner{-M_PI, M_PI};
    std::uniform_real_distribution<> start_position{0, c_D};

    for (size_t i{0}; i < c_N ; ++i) {
        auto end_position = std::cos(corner(mt)) * c_l + start_position(mt);
        if (end_position <= 0 || end_position >= c_D) {
            ++n;
        }
    }

    std::cout << "p*  = " << static_cast<double>(n) / c_N << ";\n";
    std::cout << "PI* = " << 2 * c_l * c_N / n / c_D << ";\n";

    return 0;
}

