#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"

class PlayMemoryTextScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(120, 0);

		memoryTextComp = owner->GetComponent<TextRenderComponent>();
		memoryTextComp->SetText(m_memoryText, L"±¼¸²", 3.7f, D2D1::ColorF(D2D1::ColorF::White));
	}

	void Update() override
	{
		// VRAM / DRAM / PageFile Ã¼Å©
		m_memoryText = memoryTextComp->UpdateMemoryInfo();
		memoryTextComp->SetText(m_memoryText, L"Consolas", 5, D2D1::ColorF(D2D1::ColorF::White));
	}

private:
	std::wstring m_memoryText;
	GameObject* memoryObject;
	TextRenderComponent* memoryTextComp;
};