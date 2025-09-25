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

	float GetTotalTime();	// â�� ����� ��~ ������� �ð�(�Ͻ����� ����)
	float GetPlayTime() const { return playTime; }

	void SetTotalTime(float time);
	void SetPlayTime(float time);

	// Debug
	void Pause() { m_isPaused = true; std::cout << "[Debug] �Ͻ�����" << std::endl;}
	void Resume() { m_isPaused = false; std::cout << "[Debug] �Ͻ����� ����" << std::endl;}
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

