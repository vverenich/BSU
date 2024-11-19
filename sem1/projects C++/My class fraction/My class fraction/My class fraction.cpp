#include <iostream>
#include "Fraction.h"

int main()
{
    Fraction fr(10, 1);
    std::cout << fr.GetNumerator() << "\n";
    std::cout << fr.GetDenominator() << "\n";
    fr.SetNumerator(4);
    std::cout << fr.GetNumerator() << "\n";
    std::cout << fr.GetDenominator() << "\n";
    fr.SetDenominator(1);
    return 0;
}
