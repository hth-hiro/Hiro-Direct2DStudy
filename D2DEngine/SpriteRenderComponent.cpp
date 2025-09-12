#include "pch.h"
#include "SpriteRenderComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"

void SpriteRenderComponent::Render()
{
	if (!m_bitmap) return;

	TransformComponent* transformPtr = owner->GetTransform();

	D2D1_RECT_F srcRect = D2D1::RectF(
		m_sprite.x,
		m_sprite.y,
		m_sprite.x + m_sprite.width,
		m_sprite.y + m_sprite.height
	);

	//D2DEngineWrapper

	D2DEngineWrapper::GetInstance().DrawBitmapForTransform(m_bitmap->GetBitmap(), *transformPtr, m_opacity, &srcRect, owner->isUI());
}