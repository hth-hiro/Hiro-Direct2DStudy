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

private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	LARGE_INTEGER initCounter;

	float deltaTime;
};

