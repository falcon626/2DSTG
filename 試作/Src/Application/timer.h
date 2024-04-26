#pragma once
class C_Timer
{
public:
    C_Timer() : m_bRunning(false) {}

    void Start();

    void Stop();

    void Restart();

    void Resume();

    int ElapsedSeconds();

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_stopTime;
    bool m_bRunning;
};
