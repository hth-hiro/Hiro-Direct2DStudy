#pragma once
#include "Component.h"
#include "ScriptSystem.h"

class GameObject;
class ScriptComponent :
	public Component
{
public:
	ScriptComponent()
	{
		ScriptSystem::GetInstance().Register(this);

	}
	~ScriptComponent()
	{
		ScriptSystem::GetInstance().Unregister(this);
	}

	virtual void Awake() override {}
	virtual void Start() override {}
	virtual void Update() override {}

	virtual void OnTriggerEnter(GameObject* other) {}
	virtual void OnTriggerStay(GameObject* other) {}
	virtual void OnTriggerExit(GameObject* other) {}

	virtual void OnCollisionEnter(GameObject* other) {}
	virtual void OnCollisionStay(GameObject* other) {}
	virtual void OnCollisionExit(GameObject* other) {}

	void OnEnable() override {}
	void OnDestroy() override {}

private:
};