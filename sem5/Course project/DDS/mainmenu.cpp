#include <iostream>
#include <vector>

#include "mainmenu.h"
#include "alternativeinterface.h"
#include "ddsdistributedroboticsystem.h"

MainMenu::MainMenu()
{

}

void MainMenu::runMenu() const
{
    DDSDistributedRoboticSystem system{};
    std::vector<AlternativeInterface*> vector;

    std::cout << "Добро пожаловать в менеджер РРС!\n";
    bool isMenuAlive{true};
    while (isMenuAlive) {
        std::cout << "Выберите действие:\n";
        std::cout << "\t1)Добавить данные для нового цеха.\n";
        std::cout << "\t2)Получить оперативное решение.\n";
        std::cout << "\t3)Очистить данные.\n";
        std::cout << "\t4)Выйти.\n";

        int choice;
        std::cin >> choice;

        switch (choice) {
          case 1 : {
            std::cout << "\t\nВведите название цеха:\n";
            std::string name;
            std::cout << "\tyour choice: ";
            std::cin >> name;

            std::cout << "\t\nВведите тип роботов в цехе(a, b, c):\n";
            char typeChoice;
            std::cout << "\tyour choice: ";
            std::cin >> typeChoice;

            std::cout << "\t\nВведите кол-во сотрудников:\n";
            int employeesNumber;
            std::cout << "\tyour choice: ";
            std::cin >> employeesNumber;

            std::cout << "\t\nВведите общее число роботов:\n";
            int totalNumberOfRobots;
            std::cout << "\tyour choice: ";
            std::cin >> totalNumberOfRobots;

            std::cout << "\t\nВведите число роботов в среднем состоянии:\n";
            int numberOfRobotsInMiddleState;
            std::cout << "\tyour choice: ";
            std::cin >> numberOfRobotsInMiddleState;

            std::cout << "\t\nВведите число роботов в плохом состоянии:\n";
            int numberOfRobotsInBadState;
            std::cout << "\tyour choice: ";
            std::cin >> numberOfRobotsInBadState;

            DistributedRoboticSystem* sys = new DistributedRoboticSystem();
            sys->setNameOfRoboticSystem(name);
            sys->setTypeOfRobots(new TypeOfRobot(std::to_string(typeChoice)));
            sys->setNumberOfEmployees(employeesNumber);
            sys->setTotalNumberOfRobots(totalNumberOfRobots);
            sys->setNumberOfRobotsInMiddleState(numberOfRobotsInMiddleState);
            sys->setNumberOfRobotsInBadState(numberOfRobotsInBadState);

            vector.emplace_back(sys);

            break;
          }
          case 2 : {
            AlternativeInterface* alternative = system.chooseAlternative(vector);

            std::cout << "СППР приняла решение.\n";
            std::cout << "Цех, в который поедет ремонтная бригада: " <<
                         static_cast<DistributedRoboticSystem*>(alternative)->toString();

            break;
          }
          case 3 : {
            for(size_t i{0}; i < vector.size(); ++i) {
                delete vector.at(i);
            }

            vector.clear();

            break;
          }
          case 4 : {
            for(size_t i{0}; i < vector.size(); ++i) {
                delete vector.at(i);
            }

            isMenuAlive = false;

            break;
          }
        }
    }
}
