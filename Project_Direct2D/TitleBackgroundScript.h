#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class TitleBackgroundScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* scene = owner->GetScene();

		// Background
		auto* bgObj = scene->CreateObject<GameObject>();
		auto* bgSprite = bgObj->AddComponent<SpriteRenderComponent>();
		auto bgBitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Background.webp");
		bgSprite->SetBitmap(bgBitmap);

		// Title Text
		auto* textObj = scene->CreateObject<GameObject>();
		auto* textSprite = textObj->AddComponent<SpriteRenderComponent>();
		auto textBitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Background/Titletemp.webp");
		textSprite->SetBitmap(textBitmap);
	}
};

