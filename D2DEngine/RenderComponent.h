#pragma once
#include "D2DEngineWrapper.h"
#include "Component.h"
#include "RenderSystem.h"

class RenderComponent :
	public Component
{
public:
    RenderComponent() = default;
    virtual ~RenderComponent() = default;

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