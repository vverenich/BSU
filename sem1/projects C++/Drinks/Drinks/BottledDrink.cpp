#include "BottledDrink.h"
#include<exception>

std::string BottledDrink::GetName() const
{
    return name;
}

double BottledDrink::GetVolume() const
{
    return volume;
}

void BottledDrink::SetName(std::string nam)
{
    name = nam;
}

void BottledDrink::SetVolume(double vol)
{
    if (vol <= 0) {
        throw std::runtime_error("Volume can not be negative");
    }
    else {
        volume = vol;
    }
}
