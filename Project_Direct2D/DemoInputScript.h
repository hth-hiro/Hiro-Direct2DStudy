#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/ColliderDebugRenderer.h"

class DemoInputScript : public ScriptComponent
{
public:
	bool visible = true;
	ColliderDebugRenderer* hitbox = nullptr;

	void Awake() override
	{
		hitbox = owner->GetComponent<ColliderDebugRenderer>();
	}

	void Update() override
	{
		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			if (m_CurrScene == 0) return;

			SceneManager::GetInstance().ChangeScene(m_CurrScene-1);
		}

		if (InputSystem::GetInstance().IsKeyPressed(VK_SPACE))
		{
			if (m_CurrScene >= SceneManager::GetInstance().m_vScenes.size()) return;

			SceneManager::GetInstance().ChangeScene(m_CurrScene + 1);
		}

		if (InputSystem::GetInstance().IsKeyDown(VK_F3)
			&& InputSystem::GetInstance().IsKeyPressed('B'))
		{
			visible = !visible;

			auto* scene = SceneManager::GetInstance().GetCurrentScene();
			for (auto* obj : scene->GetAllObjects())
			{
				auto* hb = obj->GetComponent<ColliderDebugRenderer>();
				if (hb)
					hb->SetVisible(visible);
			}
		}
	}

private:
	int m_CurrScene = SceneManager::GetInstance().GetCurrentSceneIndex();
};