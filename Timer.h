#pragma once
#include <windows.h>

class Timer {
public:
	Timer();
	~Timer();



	void Init();
	void Update();
	double GetDelta();
	void Pause();
	void Unpause();

	float GetFPS();



private:
	
	INT64 m_frequency, m_startTime;
	float m_ticksPerMs, m_frameTime;
	double m_deltaTime;


	void CalcFPS();
	bool m_doAvgFPS = 0;
	float m_fps;
	int m_curFrameCountIndex = 0;
	int m_maxFrameCount = 12;
	INT64 m_frames[12];



};
