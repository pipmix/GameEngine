#pragma once
#include <windows.h>

class Timer {
public:
	Timer();
	~Timer();



	void Init();
	void Update();
	double GetDelta();

private:
	INT64 m_frequency, m_startTime;
	float m_ticksPerMs, m_frameTime;
	double m_deltaTime;

};