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
	float GetTotalTime();

	void Pause() { m_isPaused = true; }
	void Resume() { m_isPaused = false; }
	bool isPaused() const { return m_isPaused; }

	void SetTimeScale(float scale) { m_timeScale = scale; }
	float GetTimeScale() const { return m_timeScale; }

private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	LARGE_INTEGER initCounter;

	float deltaTime;

	float m_timeScale = 1.0f;
	bool m_isPaused = false;
};

