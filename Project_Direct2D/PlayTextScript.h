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
			L"이미지 생성 : J\n\n30개씩 삭제 : L   전체 삭제 : C\n카메라 이동 : WASD, 마우스 휠클릭\n줌 인/줌 아웃 : Ctrl + 휠  카메라 초기화 : R\n메모리 해제 요청 : T",
			L"굴림", 3.7f, D2D1::ColorF(D2D1::ColorF::White));
	}
};

