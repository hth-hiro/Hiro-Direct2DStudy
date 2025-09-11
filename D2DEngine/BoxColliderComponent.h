#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
private:
	float width = 1.0f;
	float height = 1.0f;
	float offsetW = 0.0f;
	float offsetH = 0.0f;

public:
	BoxColliderComponent(float _width = 1.0f, float _height = 1.0f)
		: width(_width), height(_height) {}
	
	void SetSize(float w, float h, float _offsetW = 0.0f, float _offsetH = 0.0f) { width = w; height = h; offsetW = _offsetW; offsetH = _offsetH; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }

	AABB GetAABB() const override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		if (!tr) return AABB(0, 0, 0, 0);
		//if (!tr) return AABB(0, 0, 0, 0, "Null");

		auto pos = tr->GetTranslation();
		auto scale = tr->GetScale();

		float hw = std::abs(width * scale.width) * 0.5f;
		float hh = std::abs(height * scale.height) * 0.5f;

		float ow = offsetW * scale.width;
		float oh = offsetH * scale.height;

		return AABB(pos.x + ow, pos.y + oh, hw, hh);
	}
};

