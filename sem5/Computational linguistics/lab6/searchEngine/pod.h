#ifndef POD_H
#define POD_H

#include <string>
#include <vector>

class POD
{
public:
    POD();

    std::vector<std::pair<std::string, double>> informativeWords;
    std::string fileName{};
};

#endif // POD_H
