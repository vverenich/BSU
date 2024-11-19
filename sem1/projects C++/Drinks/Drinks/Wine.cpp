#include "Wine.h"
#include<exception>

Wine::Wine(std::string nam, double volum, double streng, double holdingTim)
{
    name = nam;
    SetVolume(volum);
    SetHoldingTime(holdingTim);
    SetStrength(streng);
}

double Wine::GetHoldingTime() const
{
    return holdingTime;
}

void Wine::SetHoldingTime(double h)
{
    if (h < 0) {
        throw std::runtime_error("Holding Time can not be negative");
    }
    else {
        holdingTime = h;
    }
}
