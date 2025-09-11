#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class PlayBackgroundScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* sprite = owner->GetComponent<SpriteRenderComponent>();
		auto bitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Background4th.webp");
		sprite->SetBitmap(bitmap);
	}
};

