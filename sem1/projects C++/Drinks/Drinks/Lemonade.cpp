#include "Lemonade.h"

Lemonade::Lemonade(std::string nam, double volum, Type t)
{
    name = nam;
    SetVolume(volum);
    SetType(t);
}

std::string Lemonade::GetType() const
{
    if (type == Type::CreamSoda) {
        return "CreamSoda";
    }
    if (type == Type::Citro) {
        return "Citro";
    }
    if (type == Type::Duchess) {
        return "Duchess";
    }
    if (type == Type::Buratino) {
        return "Buratino";
    }
    if (type == Type::Baikal) {
        return "Baikal";
    }
    if (type == Type::Tarhun) {
        return "Tarhun";
    }
}

void Lemonade::SetType(Type t)
{
    type = t;
}
