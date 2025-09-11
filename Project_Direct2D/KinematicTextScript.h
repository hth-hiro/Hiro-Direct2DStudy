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
		text->SetText(L"<DemoScene>\n<Kinematic>\n�� ���� ī�޶� �̵��� �����ϴ�!\nF3 + B�� ��Ʈ�ڽ��� �Ѱ� �� �� �ֽ��ϴ�!\nF6���� Player ��ġ �ʱ�ȭ", L"���� ��������", 5, D2D1::ColorF(D2D1::ColorF::White));
	}
};

