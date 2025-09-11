#pragma once
#include "GameObject.h"
#include "Component.h"
#include "AABB.h"

class ColliderComponent : public Component
{
public:
	ColliderComponent() = default;

	bool isTrigger = false;
	
	virtual AABB GetAABB() const = 0;

	bool CheckCollision(ColliderComponent* other) const
	{
		return GetAABB().Overlaps(other->GetAABB());
	}

	virtual void OnCollisionEnter(GameObject* other) {}
	virtual void OnCollisionStay(GameObject* other) {}
	virtual void OnCollisionExit(GameObject* other) {}
	
	virtual void OnTriggerEnter(GameObject* other) {}
	virtual void OnTriggerStay(GameObject* other) {}
	virtual void OnTriggerExit(GameObject* other) {}

	virtual void OnEnable() {}
	virtual void OnDestroy() {}
};