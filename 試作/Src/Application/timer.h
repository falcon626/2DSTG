#pragma once
class C_Timer
{
public:
	C_Timer(){}
	~C_Timer(){}

	void StartTime();
	int GetElapsedTime();

private:
	std::chrono::steady_clock::time_point m_startTime;
};
