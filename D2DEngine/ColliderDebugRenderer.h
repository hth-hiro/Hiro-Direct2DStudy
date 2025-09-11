#pragma once
#include "TransformComponent.h"
#include "RenderComponent.h"

class ColliderDebugRenderer : public RenderComponent
{
public:
	void SetVisible(bool v) { visible = v; }

	void Render() override;
	void Update() override {}

private:
	bool visible = true;
};

