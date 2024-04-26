#include "timer.h"

void C_Timer::Start()
{
    if (!m_bRunning) {
        auto now = std::chrono::steady_clock::now();
        if (m_startTime != std::chrono::steady_clock::time_point()) m_startTime += (now - m_stopTime);
        else m_startTime = now;
        m_bRunning       = true;
    }
}

void C_Timer::Stop()
{
    if (m_bRunning) {
        m_stopTime = std::chrono::steady_clock::now();
        m_bRunning = false;
    }
}

void C_Timer::Restart()
{
    Stop();
    m_startTime = std::chrono::steady_clock::now();
    m_bRunning  = true;
}

void C_Timer::Resume()
{
    if (!m_bRunning) {
        m_startTime += (std::chrono::steady_clock::now() - m_stopTime);
        m_bRunning   = true;
    }
}

int C_Timer::ElapsedSeconds()
{
    std::chrono::steady_clock::time_point endTime = m_bRunning ? std::chrono::steady_clock::now() : m_stopTime;
    return std::chrono::duration_cast<std::chrono::seconds>(endTime - m_startTime).count();
}
