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

	if (!m_isPaused)
	{
		deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;
		deltaTime *= m_timeScale;
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
