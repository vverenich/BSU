#include "timer.h"

Timer::Timer()
{

}

void Timer::reset()
{
     m_beg = clock_type::now();
}

double Timer::elapsed() const
{
    return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
}
