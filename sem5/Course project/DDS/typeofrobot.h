#ifndef TYPEOFROBOT_H
#define TYPEOFROBOT_H

#include <string>
#include <string_view>

class TypeOfRobot {
  public:
    TypeOfRobot() = default;
    TypeOfRobot(const std::string& type);
    TypeOfRobot(TypeOfRobot&& type);
    TypeOfRobot(TypeOfRobot* type);
    TypeOfRobot& operator=(TypeOfRobot&& type);

    std::string toString() const;

  private:
    std::string m_Type;
};

#endif // TYPEOFROBOT_H
