#pragma once
#include "Singleton.h"

class Time : public Singleton<Time>
{
public:
	Time() = default;
	~Time() = default;

	void Initialize();
	void Update();

	float GetDeltaTime();

	float GetTotalTime();	// 창이 실행된 후~ 현재까지 시간(일시정지 포함)
	float GetPlayTime() const { return playTime; }

	void SetTotalTime(float time);
	void SetPlayTime(float time);

	// Debug
	void Pause() { m_isPaused = true; std::cout << "[Debug] 일시정지" << std::endl;}
	void Resume() { m_isPaused = false; std::cout << "[Debug] 일시정지 해제" << std::endl;}
	bool isPaused() const { return m_isPaused; }

	void SetTimeScale(float scale) { m_timeScale = scale; }
	float GetTimeScale() const { return m_timeScale; }

private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	LARGE_INTEGER initCounter;

	float deltaTime = 0.0f;

	float playTime = 0.0f;
	float totalTime = 0.0f;

	float m_timeScale = 1.0f;
	bool m_isPaused = false;

};

