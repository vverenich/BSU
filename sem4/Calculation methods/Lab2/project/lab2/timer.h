#ifndef TIMER_H
#define TIMER_H


#include <chrono> // for std::chrono functions

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_type> m_beg { clock_type::now() };

public:
    void reset();

    double elapsed() const;
};
#endif // TIMER_H
