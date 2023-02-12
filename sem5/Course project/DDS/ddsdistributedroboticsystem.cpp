#include <algorithm>
#include <set>

#include "ddsdistributedroboticsystem.h"

template <class T>
int getIndex(std::vector<T> v, T K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {

        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}

AlternativeInterface* DDSDistributedRoboticSystem::chooseAlternative(const std::vector<AlternativeInterface*>& alternatives)
{
    std::vector<size_t> ratingByTotalNumber = compareAlternativesByTotalNumberOfRobots(alternatives);
    std::vector<size_t> ratingByNumberOfRobotsInMiddleState = compareAlternativesByNumberOfRobotsInMiddleState(alternatives);
    std::vector<size_t> ratingByNumberOfRobotsInBadState = compareAlternativesByNumberOfRobotsinBadState(alternatives);
    std::vector<size_t> ratingByNumberOfEmployees = compareAlternativesByNumberOfEmployees(alternatives);
    std::vector<size_t> ratingByType = compareAlternativesByType(alternatives);

    std::vector<size_t> sum(alternatives.size());
    for(size_t i{0}; i < sum.size(); ++i) {
        sum.at(i) = ratingByNumberOfEmployees.at(i) +
                    ratingByNumberOfRobotsInBadState.at(i) +
                    ratingByNumberOfRobotsInMiddleState.at(i) +
                    ratingByTotalNumber.at(i) +
                    ratingByType.at(i);
    }

    auto maxValueIter = std::max_element(sum.begin(), sum.end());
    size_t index = maxValueIter - sum.begin();

    return alternatives.at(index);
}

std::vector<size_t> DDSDistributedRoboticSystem::compareAlternativesByTotalNumberOfRobots(const std::vector<AlternativeInterface*> &alternatives) const
{
    std::vector<size_t> result(alternatives.size());

    std::set<size_t> uniqueValues;
    for(const auto& alternative : alternatives) {
        uniqueValues.insert(static_cast<DistributedRoboticSystem*>(alternative)->getTotalNumberOfRobots());
    }
    std::vector<size_t> sortedUniqueValues(uniqueValues.begin(), uniqueValues.end());
    std::sort(sortedUniqueValues.begin(), sortedUniqueValues.end());

    for(size_t i{0}; i < result.size(); ++i) {
        size_t value = static_cast<DistributedRoboticSystem*>(alternatives.at(i))->getTotalNumberOfRobots();
        result.at(i) = getIndex(sortedUniqueValues, value);
    }

    return result;
}

std::vector<size_t> DDSDistributedRoboticSystem::compareAlternativesByNumberOfRobotsInMiddleState(const std::vector<AlternativeInterface *> &alternatives) const
{
    std::vector<size_t> result(alternatives.size());

    std::set<size_t> uniqueValues;
    for(const auto& alternative : alternatives) {
        uniqueValues.insert(static_cast<DistributedRoboticSystem*>(alternative)->getNumberOfRobotsInMiddleState());
    }
    std::vector<size_t> sortedUniqueValues(uniqueValues.begin(), uniqueValues.end());
    std::sort(sortedUniqueValues.begin(), sortedUniqueValues.end(), std::greater<size_t>());

    for(size_t i{0}; i < result.size(); ++i) {
        size_t value = static_cast<DistributedRoboticSystem*>(alternatives.at(i))->getNumberOfRobotsInMiddleState();
        result.at(i) = getIndex(sortedUniqueValues, value);
    }

    return result;
}

std::vector<size_t> DDSDistributedRoboticSystem::compareAlternativesByNumberOfRobotsinBadState(const std::vector<AlternativeInterface *> &alternatives) const
{
    std::vector<size_t> result(alternatives.size());

    std::set<size_t> uniqueValues;
    for(const auto& alternative : alternatives) {
        uniqueValues.insert(static_cast<DistributedRoboticSystem*>(alternative)->getNumberOfRobotsInBadState());
    }
    std::vector<size_t> sortedUniqueValues(uniqueValues.begin(), uniqueValues.end());
    std::sort(sortedUniqueValues.begin(), sortedUniqueValues.end());

    for(size_t i{0}; i < result.size(); ++i) {
        size_t value = static_cast<DistributedRoboticSystem*>(alternatives.at(i))->getNumberOfRobotsInBadState();
        result.at(i) = getIndex(sortedUniqueValues, value);
    }

    return result;
}

std::vector<size_t> DDSDistributedRoboticSystem::compareAlternativesByNumberOfEmployees(const std::vector<AlternativeInterface *> &alternatives) const
{
    std::vector<size_t> result(alternatives.size());

    std::set<size_t> uniqueValues;
    for(const auto& alternative : alternatives) {
        uniqueValues.insert(static_cast<DistributedRoboticSystem*>(alternative)->getNumberOfEmployees());
    }
    std::vector<size_t> sortedUniqueValues(uniqueValues.begin(), uniqueValues.end());
    std::sort(sortedUniqueValues.begin(), sortedUniqueValues.end(), std::greater<size_t>());

    for(size_t i{0}; i < result.size(); ++i) {
        size_t value = static_cast<DistributedRoboticSystem*>(alternatives.at(i))->getNumberOfEmployees();
        result.at(i) = getIndex(sortedUniqueValues, value);
    }

    return result;
}

std::vector<size_t> DDSDistributedRoboticSystem::compareAlternativesByType(const std::vector<AlternativeInterface *> &alternatives) const
{
    std::vector<size_t> result(alternatives.size());

    std::set<std::string> uniqueValues;
    for(const auto& alternative : alternatives) {
        uniqueValues.insert(static_cast<DistributedRoboticSystem*>(alternative)->getTypeOfRobots());
    }
    std::vector<std::string> sortedUniqueValues(uniqueValues.begin(), uniqueValues.end());
    std::sort(sortedUniqueValues.begin(), sortedUniqueValues.end(), std::greater<std::string>());

    for(size_t i{0}; i < result.size(); ++i) {
        std::string value = static_cast<DistributedRoboticSystem*>(alternatives.at(i))->getTypeOfRobots();
        result.at(i) = getIndex(sortedUniqueValues, value);
    }

    return result;
}
