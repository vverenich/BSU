#include "distributedroboticsystem.h"

DistributedRoboticSystem::DistributedRoboticSystem()
{

}

void DistributedRoboticSystem::setNameOfRoboticSystem(const std::string &name)
{
    m_NameOfRoboticSystem = name;
}

void DistributedRoboticSystem::setTotalNumberOfRobots(const size_t totalNumberOfRobots)
{
    m_TotalNumberOfRobots = totalNumberOfRobots;
}

void DistributedRoboticSystem::setNumberOfRobotsInBadState(const size_t numberOfRobotsInBadState)
{
    m_NumberOfRobotsInBadState = numberOfRobotsInBadState;
}

void DistributedRoboticSystem::setNumberOfRobotsInMiddleState(const size_t numberOfRobotsInMiddleState)
{
    m_NumberOfRobotsInMiddleState = numberOfRobotsInMiddleState;
}

void DistributedRoboticSystem::setNumberOfEmployees(const size_t numberOfEmployees)
{
    m_NumberOfEmployees = numberOfEmployees;
}

void DistributedRoboticSystem::setTypeOfRobots(TypeOfRobot* type)
{
    m_TypeOfRobot = std::make_unique<TypeOfRobot>(type);
}

std::string DistributedRoboticSystem::getNameOfRoboticSystem() const
{
    return m_NameOfRoboticSystem;
}

size_t DistributedRoboticSystem::getTotalNumberOfRobots() const
{
    return m_TotalNumberOfRobots;
}

size_t DistributedRoboticSystem::getNumberOfRobotsInBadState() const
{
    return m_NumberOfRobotsInBadState;
}

size_t DistributedRoboticSystem::getNumberOfRobotsInMiddleState() const
{
    return m_NumberOfRobotsInMiddleState;
}

size_t DistributedRoboticSystem::getNumberOfEmployees() const
{
    return m_NumberOfEmployees;
}

std::string DistributedRoboticSystem::getTypeOfRobots() const
{
    return m_TypeOfRobot->toString();
}

std::string DistributedRoboticSystem::toString()
{
    return m_NameOfRoboticSystem;
}
