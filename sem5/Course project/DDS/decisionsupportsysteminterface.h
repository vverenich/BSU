#ifndef DECISIONSUPPORTSYSTEM_H
#define DECISIONSUPPORTSYSTEM_H

#include <vector>

#include "alternativeinterface.h"

class DecisionSupportSystemInterface {
  public:
    DecisionSupportSystemInterface() = default;

    virtual AlternativeInterface* chooseAlternative(const std::vector<AlternativeInterface*>& alternatives) = 0;
};

#endif // DECISIONSUPPORTSYSTEM_H
