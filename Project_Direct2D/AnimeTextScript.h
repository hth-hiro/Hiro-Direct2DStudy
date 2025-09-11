#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class AnimeTextScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(80, 5);
		auto* text = owner->GetComponent<TextRenderComponent>();
		text->SetText(L"<Transfrom>\n\n\n�̵� : ����Ű\n���� : X", L"���� ���", 5, D2D1::ColorF(D2D1::ColorF::White));
	}
};