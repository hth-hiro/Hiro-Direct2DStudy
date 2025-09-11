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

	// ���� �Լ� �߰�?

private:
	float m_opacity;	// ��Ʈ�� ����
	std::shared_ptr<BitmapResource> m_bitmap;
	Sprite m_sprite;
};