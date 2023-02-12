#include "typeofrobot.h"

TypeOfRobot::TypeOfRobot(TypeOfRobot &&type)
{
    std::swap(*this, type);
}

TypeOfRobot::TypeOfRobot(const std::string &type)
{
    m_Type = type;
}

TypeOfRobot::TypeOfRobot(TypeOfRobot *type)
{
    m_Type = type->toString();
}

TypeOfRobot &TypeOfRobot::operator=(TypeOfRobot &&type)
{
    std::swap(*this, type);

    return *this;
}

std::string TypeOfRobot::toString() const
{
    return m_Type;
}
