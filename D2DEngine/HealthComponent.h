#pragma once
#include "Component.h"
#include "GameObject.h"
#include "MultiDelegate.h"

class HealthComponent :
	public Component
{
public:
	int HP = 100;

	// std::function<void(int, int)> 의 콜백을 등록받음
	MultiDelegate<int, int> onChangeHealth;

	void TakeDamage(int value)
	{
		int result = std::max<int>(0, HP - value);
		SetHP(result);
	}

	void SetHP(int value)
	{
		if (HP != value)
		{
			int prev = HP;
			HP = value;
			onChangeHealth.BroadCast(prev, HP);
		}
	}

	void OnEnable() override {}
	void OnDestroy() override {}

	void Update() override {}
};

