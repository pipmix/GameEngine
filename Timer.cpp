
#include "Timer.h"



Timer::Timer() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	m_ticksPerMs = (float)(m_frequency / 1000);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);




}
Timer::~Timer() {}
void Timer::Init()
{
}
void Timer::Update() {
	INT64 currentTime;
	float timeDifference;
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeDifference = (float)(currentTime - m_startTime);
	m_frameTime = timeDifference / m_ticksPerMs;
	m_startTime = currentTime;


	CalcFPS();
}
double Timer::GetDelta() { return m_frameTime; }


void Timer::Pause() {

}

void Timer::Unpause() {


}


void Timer::CalcFPS() {

	m_frames[m_curFrameCountIndex++] = m_frameTime;

	if (m_curFrameCountIndex >= m_maxFrameCount) {
		m_curFrameCountIndex = 0;
		if (m_doAvgFPS = 0)m_doAvgFPS = 1;
	}

	if (m_doAvgFPS) {
		INT64 tempAvg = 0;
		for (int i = 0; i < m_maxFrameCount; i++) tempAvg += m_frames[i];
		tempAvg /= m_maxFrameCount;
		if (tempAvg != 0)m_fps = 1000.0f / (float)tempAvg;
	}

}

float Timer::GetFPS() {
	return m_fps;
}