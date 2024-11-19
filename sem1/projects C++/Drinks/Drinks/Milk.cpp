#include "Milk.h"
#include<exception>

Milk::Milk(std::string nam, double volum, double fatCont)
{
    name = nam;
    SetVolume(volum);
    SetFatContent(fatCont);
}

double Milk::GetFatContent() const
{
    return fatContent;
}

void Milk::SetFatContent(double fatCont)
{
    if (fatCont <= 0 || fatCont > 100) {
        throw std::runtime_error("Strength belongs to the interval (0, 100]");
    }
    else {
        fatContent = fatCont;
    }
}
