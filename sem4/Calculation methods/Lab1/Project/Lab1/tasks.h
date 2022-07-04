#ifndef TASKS_H
#define TASKS_H

#include <random>
#include <iostream>
#include <dir.h>

#include "printer.h"
#include "matrix.h"
#include "gaussjordan.h"
#include "gausscolumnselection.h"
#include "gauss.h"
#include "relaxation.h"
#include "timer.h"

constexpr auto N{4};

class Tasks
{
    Printer* m_printer;

    Matrix m_A{};
    Matrix m_y{};
    Matrix m_b{};
    Matrix m_maxCondMatrix{};

    std::string m_dirNameForTasks1_8{"tasks1-8"};
    std::string m_dirNameForTask9A1{"task9A1"};
    std::string m_dirNameForTask9A2{"task9A2"};
    std::string m_dirNameForTask10{"task10"};

    Timer m_timer{};
public:
    Tasks();
    ~Tasks();

    // Additional methods
    double fRand(double fMin, double fMax);

    // Tasks in lab
    void performTask1(bool);
    void performTask2(bool);
    double performTask3(bool);
    Matrix performTask4(bool);
    Matrix performTask5(bool);
    Matrix performTask6(bool);
    Matrix performTask7(bool);
    void performTask8();
    void performTask9();
    void performTask10();

};

#endif // TASKS_H
