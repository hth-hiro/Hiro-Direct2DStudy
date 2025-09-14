#include "pch.h"
#include "Time.h"

void Time::Initialize()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&initCounter);
	prevCounter = initCounter;
}

void Time::Update()
{
	QueryPerformanceCounter(&currentCounter);

	float frameTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;

	if (!m_isPaused)
	{
		deltaTime = frameTime * m_timeScale;
		playTime += deltaTime;
	}
	else
	{
		deltaTime = 0.0f;
	}

	prevCounter = currentCounter;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

float Time::GetTotalTime()
{
	return static_cast<float>(currentCounter.QuadPart - initCounter.QuadPart) / frequency.QuadPart;
}

void Time::SetTotalTime(float time)
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	initCounter.QuadPart = counter.QuadPart - static_cast<LONGLONG>(time * frequency.QuadPart);
}

void Time::SetPlayTime(float time)
{
	// 현재 저장된 플레이 타임으로 설정
	playTime = time;
}