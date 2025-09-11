#pragma once
#include <unordered_map>
#include <unordered_set>
#include "BoxColliderComponent.h"

class ColliderSystem
{
public:
	void Enter();
	void Update();

private:
	//std::vector<BoxColliderComponent*> m_Colliders;

	std::unordered_map<GameObject*, std::unordered_set<GameObject*>> m_PrevOverlaps;
	std::unordered_map<GameObject*, std::unordered_set<GameObject*>> m_CurrOverlaps;
};