#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<clock_type> m_beg { clock_type::now() };
public:
    Timer();

    void reset();
    double elapsed() const;
};

#endif // TIMER_H
