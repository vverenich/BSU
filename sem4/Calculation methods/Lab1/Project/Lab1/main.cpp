#include <iostream>

#include "tasks.h"

int main()
{
    Tasks tasks;

    std::cout<<"\n\nExecuting task number 1...";
    tasks.performTask1(1);
    std::cout<<"\n\nExecuting task number 1 finished";

    std::cout<<"\n\nExecuting task number 2...";
    tasks.performTask2(1);
    std::cout<<"\n\nExecuting task number 2 finished";

    std::cout<<"\n\nExecuting task number 3...";
    tasks.performTask3(1);
    std::cout<<"\n\nExecuting task number 3 finished";

    std::cout<<"\n\nExecuting task number 4...";
    tasks.performTask4(1);
    std::cout<<"\n\nExecuting task number 4 finished";

    std::cout<<"\n\nExecuting task number 5...";
    tasks.performTask5(1);
    std::cout<<"\n\nExecuting task number 5 finished";

    std::cout<<"\n\nExecuting task number 6...";
    tasks.performTask6(1);
    std::cout<<"\n\nExecuting task number 6 finished";

    std::cout<<"\n\nExecuting task number 7...";
    tasks.performTask7(1);
    std::cout<<"\n\nExecuting task number 7 finished";

    std::cout<<"\n\nExecuting task number 8...";
    tasks.performTask8();
    std::cout<<"\n\nExecuting task number 8 finished";

    std::cout<<"\n\nExecuting task number 9...";
    tasks.performTask9();
    std::cout<<"\n\nExecuting task number 9 finished";

    std::cout<<"\n\nExecuting task number 10...";
    tasks.performTask10();
    std::cout<<"\n\nExecuting task number 10 finished";

    return 0;
}
