#pragma once
#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "Time.h"
#include "SceneManager.h"
#include "BoxColliderComponent.h"

class DynamicComponent : public Component
{
public:
	DynamicComponent()
	{
		gravity = 980.0f;
	}

	// Setter
	void SetGravity(float _gravity) { gravity = _gravity; }
	void SetVelocity(float vX, float vY) { velocityX = vX; velocityY = vY; }
	void SetGround(bool value) { isGrounded = value; }

	// Getter
	float GetVelocityX() { return velocityX; }
	float GetVelocityY() { return velocityY; }

	void AddForce(float fX, float fY) { velocityX += fX; velocityY += fY; }

	void Update() override
	{
		// Debug
		//std::cout << "[Debug] isGround : " << isGrounded << std::endl;

		auto* tr = owner->GetComponent<TransformComponent>();
		if (!tr) return;

		auto* myCol = owner->GetComponent<BoxColliderComponent>();

		if (!myCol) return;

		// 시간 보정
		float dt = Time::GetInstance().GetDeltaTime();
		if (dt > 0.1f) dt = 0.016f;

		velocityY -= gravity * dt;
		auto pos = tr->GetTranslation();

		float nextX = pos.x + velocityX * dt;
		float nextY = pos.y + velocityY * dt;

		nextPositionX = nextX;
		nextPositionY = nextY;
	}

	bool isGrounded = false;
	float nextPositionX = 0.0f;
	float nextPositionY = 0.0f;

	virtual void OnEnable() {}
	virtual void OnDestroy() {}

private:
	float gravity = 980.0f;
	float velocityX = 0.0f;
	float velocityY = 0.0f;
};

