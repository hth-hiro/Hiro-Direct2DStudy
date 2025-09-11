#pragma once
#include <string>

#include "RenderComponent.h"
#include "BitmapResource.h"
#include "Sprite.h"

class SpriteRenderComponent :
	public RenderComponent
{
public:
	//SpriteRenderComponent() {}
	~SpriteRenderComponent() {}

	void Render() override;
	void Update() override {}

	void SetBitmap(std::shared_ptr<BitmapResource> bitmap)
	{
		m_bitmap = bitmap;
	}

	void SetSpriteInfo(const Sprite& sprite, std::shared_ptr<BitmapResource> bitmap)
	{
		m_sprite = sprite;
		m_bitmap = bitmap;
	}

	// 헬퍼 함수 추가?

private:
	float m_opacity;	// 비트맵 투명도
	std::shared_ptr<BitmapResource> m_bitmap;
	Sprite m_sprite;
};