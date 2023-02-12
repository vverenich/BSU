#ifndef ALTERNATIVEINTERFACE_H
#define ALTERNATIVEINTERFACE_H

#include <string>

class AlternativeInterface {
  public:
    AlternativeInterface() = default;

    virtual std::string toString() = 0;
};

#endif // ALTERNATIVEINTERFACE_H
