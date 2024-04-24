#include "timer.h"

void C_Timer::start()
{
    if (!running) {
        auto now = std::chrono::steady_clock::now();
        if (startTime != std::chrono::steady_clock::time_point()) {
            // ˆê’â~‚µ‚Ä‚¢‚½ê‡AŒo‰ßŠÔ‚ğ•â³‚·‚é
            startTime += (now - stopTime);
        }
        else {
            startTime = now;
        }
        running = true;
    }
}

void C_Timer::stop()
{
    if (running) {
        stopTime = std::chrono::steady_clock::now();
        running = false;
    }
}

void C_Timer::restart()
{
    stop();
    startTime = std::chrono::steady_clock::now();
    running = true;
}

void C_Timer::resume()
{
    if (!running) {
        startTime += (std::chrono::steady_clock::now() - stopTime);
        running = true;
    }
}

int C_Timer::elapsedSeconds()
{
    std::chrono::steady_clock::time_point endTime = running ? std::chrono::steady_clock::now() : stopTime;
    return std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
}
