#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/ButtonComponent.h"
#include "../D2DEngine/SceneManager.h"

class ReturnButtonScript : public ScriptComponent
{
public:
	void Start() override
	{
		auto button = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Back.png");
		m_Button = owner->AddComponent<ButtonComponent>();
		m_Button->CreateButton(owner, button, 0, 0, 100, 100);
	}

	void Update() override
	{
		m_SceneIndex = SceneManager::GetInstance().GetCurrentSceneIndex();

		if (m_Button && m_Button->OnClick())
		{
			if (m_SceneIndex < 0) return;

			SceneManager::GetInstance().ChangeScene(m_SceneIndex - 1);
		}
	}

private:
	ButtonComponent* m_Button = nullptr;
	int m_SceneIndex;
};

