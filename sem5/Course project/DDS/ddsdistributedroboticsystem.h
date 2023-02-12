#ifndef DDSDISTRIBUTEDROBOTICSYSTEM_H
#define DDSDISTRIBUTEDROBOTICSYSTEM_H

#include "decisionsupportsysteminterface.h"
#include "distributedroboticsystem.h"

class DDSDistributedRoboticSystem : public DecisionSupportSystemInterface{
  public:
    DDSDistributedRoboticSystem() = default;

    virtual AlternativeInterface* chooseAlternative(const std::vector<AlternativeInterface*>& alternatives) override final;
    std::vector<size_t> compareAlternativesByTotalNumberOfRobots(const std::vector<AlternativeInterface*>& alternatives) const;
    std::vector<size_t> compareAlternativesByNumberOfRobotsInMiddleState(const std::vector<AlternativeInterface*>& alternatives) const;
    std::vector<size_t> compareAlternativesByNumberOfRobotsinBadState(const std::vector<AlternativeInterface*>& alternatives) const;
    std::vector<size_t> compareAlternativesByNumberOfEmployees(const std::vector<AlternativeInterface*>& alternatives) const;
    std::vector<size_t> compareAlternativesByType(const std::vector<AlternativeInterface*>& alternatives) const;
};

#endif // DDSDISTRIBUTEDROBOTICSYSTEM_H
