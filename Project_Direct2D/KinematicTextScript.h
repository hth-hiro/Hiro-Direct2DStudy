#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class KinematicTextScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(80, 5);

		auto* text = owner->GetComponent<TextRenderComponent>();
		text->SetText(L"<DemoScene>\n<Kinematic>\n이 씬은 카메라 이동이 없습니다!\nF3 + B로 히트박스를 켜고 끌 수 있습니다!\nF6으로 Player 위치 초기화", L"한컴 말랑말랑", 5, D2D1::ColorF(D2D1::ColorF::White));
	}
};

