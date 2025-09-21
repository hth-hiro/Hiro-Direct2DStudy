#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/Scene.h"

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
		auto* texTransform = textObj->GetComponent<TransformComponent>();
		auto textBitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Background/Titletemp.webp");
		textSprite->SetBitmap(textBitmap);
		// 타이틀 위치 임시 세팅
		texTransform->SetTranslation(0, D2DEngineWrapper::GetInstance().m_ClientHeight / 2.0f - 200);
	}
};

