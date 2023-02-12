#ifndef DISTRIBUTEDROBOTICSYSTEM_H
#define DISTRIBUTEDROBOTICSYSTEM_H

#include <memory>
#include <string_view>

#include <stdio.h>

#include "typeofrobot.h"
#include "alternativeinterface.h"

class DistributedRoboticSystem : public AlternativeInterface{
  public:
    DistributedRoboticSystem();
    void setNameOfRoboticSystem(const std::string& name);
    void setTotalNumberOfRobots(const size_t totalNumberOfRobots);
    void setNumberOfRobotsInBadState(const size_t numberOfRobotsInBadState);
    void setNumberOfRobotsInMiddleState(const size_t numberOfRobotsInMiddleState);
    void setNumberOfEmployees(const size_t numberOfEmployees);
    void setTypeOfRobots(TypeOfRobot* type);

    std::string getNameOfRoboticSystem() const;
    size_t getTotalNumberOfRobots() const;
    size_t getNumberOfRobotsInBadState() const;
    size_t getNumberOfRobotsInMiddleState() const;
    size_t getNumberOfEmployees() const;
    std::string getTypeOfRobots() const;

    virtual std::string toString() override final;

  private:
    size_t m_TotalNumberOfRobots{};
    size_t m_NumberOfRobotsInBadState{};
    size_t m_NumberOfRobotsInMiddleState{};
    size_t m_NumberOfEmployees{};
    std::unique_ptr<TypeOfRobot> m_TypeOfRobot{nullptr};
    std::string m_NameOfRoboticSystem{};
};

#endif // DISTRIBUTEDROBOTICSYSTEM_H
