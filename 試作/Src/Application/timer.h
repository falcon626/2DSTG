#pragma once
class C_Timer
{
public:
    C_Timer() : running(false) {}

    void start();

    void stop();

    void restart();

    void resume();

    int elapsedSeconds();

private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point stopTime;
    bool running;
};
