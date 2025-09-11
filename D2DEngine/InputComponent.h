#pragma once
#include "Component.h"
#include "InputSystem.h"
#include "TransformComponent.h"

class InputComponent :
	public Component
{
public:
	InputComponent() {}
	virtual ~InputComponent() = default;
	
	virtual void Update() override;
	//void Update();
	virtual void OnEnable() override {}
	virtual void OnDestroy() override {}
};