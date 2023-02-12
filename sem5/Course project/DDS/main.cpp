#include <iostream>

/*
#include "distributedroboticsystem.h"
#include "ddsdistributedroboticsystem.h"
*/
#include "mainmenu.h"

using namespace std;

int main()
{
    /*
    DistributedRoboticSystem sys1;
    sys1.setTypeOfRobots(new TypeOfRobot("a"));
    sys1.setNumberOfEmployees(15);
    sys1.setTotalNumberOfRobots(10);
    sys1.setNumberOfRobotsInMiddleState(2);
    sys1.setNumberOfRobotsInBadState(1);

    DistributedRoboticSystem sys2;
    sys2.setTypeOfRobots(new TypeOfRobot("b"));
    sys2.setNumberOfEmployees(5);
    sys2.setTotalNumberOfRobots(15);
    sys2.setNumberOfRobotsInMiddleState(3);
    sys2.setNumberOfRobotsInBadState(5);

    DistributedRoboticSystem sys3;
    sys3.setTypeOfRobots(new TypeOfRobot("c"));
    sys3.setNumberOfEmployees(10);
    sys3.setTotalNumberOfRobots(12);
    sys3.setNumberOfRobotsInMiddleState(1);
    sys3.setNumberOfRobotsInBadState(2);

    std::vector<AlternativeInterface*> vector;
    vector.push_back(&sys1);
    vector.push_back(&sys2);
    vector.push_back(&sys3);

    DDSDistributedRoboticSystem system{};
    AlternativeInterface* alternative = system.chooseAlternative(vector);
    std::cout << static_cast<DistributedRoboticSystem*>(alternative)->getTypeOfRobots();
    */
    MainMenu menu;
    menu.runMenu();
}
