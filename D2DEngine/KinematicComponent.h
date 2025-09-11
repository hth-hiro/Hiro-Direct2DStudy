#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "Time.h"
#include "SceneManager.h"
#include "BoxColliderComponent.h"

class KinematicComponent : public Component
{
public:
	KinematicComponent() = default;

	void SetVelocity(float vX, float vY) { velocityX = vX; velocityY = vY; }
	
	float GetVelocityX() { return velocityX; }
	float GetVelocityY() { return velocityY; }

	void AddForce(float fX, float fY) { velocityX += fX; velocityY += fY; }

	void Update() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		if (!tr) return;

		auto* myCol = owner->GetComponent<BoxColliderComponent>();
		if (!myCol) return;

		float dt = Time::GetInstance().GetDeltaTime();

		auto pos = tr->GetTranslation();

		float nextX = pos.x + velocityX * dt;
		float nextY = pos.y + velocityY * dt;

		auto* scene = SceneManager::GetInstance().GetCurrentScene();

		AABB horizontal(nextX, pos.y, myCol->GetAABB().halfW, myCol->GetAABB().halfH);
		for (GameObject* other : scene->GetAllObjects())
		{
			if (other == owner) continue;

			auto* otherCol = other->GetComponent<BoxColliderComponent>();
			if (!otherCol) continue;

			const AABB& otherAABB = otherCol->GetAABB();

			if (horizontal.Blocks(otherAABB))
			{
				Direction dir = horizontal.GetCollisionDirection(otherAABB);
				if (dir == Direction::Left || dir == Direction::Right)
				{
					velocityX = 0;
					nextX = pos.x;
				}
			}

		}

		AABB vertical(pos.x, nextY, myCol->GetAABB().halfW, myCol->GetAABB().halfH);
		for (GameObject* other : scene->GetAllObjects())
		{
			if (other == owner) continue;
		
			auto* otherCol = other->GetComponent<BoxColliderComponent>();
			if (!otherCol) continue;

			const AABB& otherAABB = otherCol->GetAABB();

			if (vertical.Blocks(otherAABB))
			{
				Direction dir = vertical.GetCollisionDirection(otherAABB);
				if (dir == Direction::Top || dir == Direction::Bottom)
				{
					velocityY = 0;
					nextY = pos.y;
				}
			}
		}
		
		nextPositionX = nextX;
		nextPositionY = nextY;

		// 일단 여기 제거해놓고 생각해보자;;;
		//tr->SetTranslation(nextX, nextY);
	}

	virtual void OnEnable() {}
	virtual void OnDestroy() {}

	float nextPositionX = 0.0f;
	float nextPositionY = 0.0f;

private:
	float velocityX = 0.0f;
	float velocityY = 0.0f;
};