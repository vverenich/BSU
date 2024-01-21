#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <memory>

#include "Model.h"
#include "LargeObject.h"

class Model {
  public:
    Model();

    void liveTheDay();

    size_t m_NumberOfCities{};
    std::vector<std::vector<LargeObject>> m_Objects{};
};

#endif // MODEL_H
