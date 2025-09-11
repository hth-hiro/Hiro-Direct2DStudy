#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class TitleTextScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(0, 0);

		auto* text = owner->GetComponent<TextRenderComponent>();
		text->SetText(L"Project Sekai\n\nPress ENTER to Start", L"Consolas", 5, D2D1::ColorF(D2D1::ColorF::Black));
	}
};