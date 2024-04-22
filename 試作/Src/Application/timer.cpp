#include "timer.h"

void C_Timer::StartTime()
{
    m_startTime = std::chrono::steady_clock::now();
}

int C_Timer::GetElapsedTime()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime).count();
    return static_cast<int>(elapsedTime);
}
