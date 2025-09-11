#pragma once
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class PlayTextScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(28, 0);
		auto* text = owner->GetComponent<TextRenderComponent>();
		text->SetText(
			L"�̹��� ���� : J\n\n30���� ���� : L   ��ü ���� : C\nī�޶� �̵� : WASD, ���콺 ��Ŭ��\n�� ��/�� �ƿ� : Ctrl + ��  ī�޶� �ʱ�ȭ : R\n�޸� ���� ��û : T",
			L"����", 3.7f, D2D1::ColorF(D2D1::ColorF::White));
	}
};

