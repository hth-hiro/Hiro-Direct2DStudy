#pragma once
#include "Component.h"
#include "RenderSystem.h"
// ButtonComponent
// SliderComponent
// TextComponent

class UIComponent : public Component
{
public:
	UIComponent() = default;
	virtual ~UIComponent() = default;

	virtual void Render() = 0;
	virtual void Update() override {}

	virtual void OnEnable() override
	{
		RenderSystem::GetInstance().Register(this);
	}
	virtual void OnDestroy() override
	{
		RenderSystem::GetInstance().Unregister(this);
	}
};

