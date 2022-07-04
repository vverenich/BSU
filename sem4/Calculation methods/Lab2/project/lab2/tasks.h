#ifndef TASKS_H
#define TASKS_H

#include <functional>
#include <fstream>

#include "timer.h"
#include "matrix.h"
#include "gauss.h"

class Tasks
{
private:
    Timer m_timer{};
public:
    Tasks();

    void performTask1();
    void performTask2();
    void performTask3();
};

#endif // TASKS_H
