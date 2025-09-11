#pragma once
#include "../D2DEngine/D2DEngineWrapper.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/ResourceManager.h"
#include "../D2DEngine/AudioComponent.h"
#include "../D2DEngine/Random.h"
#include "Wonderhoy.h"

class PlayInputScript : public ScriptComponent
{
public:
	void Start() override
	{
		m_Scene = SceneManager::GetInstance().GetCurrentScene();
	}

	void Update() override
	{
		// Scene Change
		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			SceneManager::GetInstance().ChangeScene(0);
		}

		if (InputSystem::GetInstance().IsKeyPressed(VK_SPACE))
		{
			SceneManager::GetInstance().ChangeScene(2);
		}

		// Resource Manager O
		if (InputSystem::GetInstance().IsKeyPressed('J'))
		{
			// Audio Play
			if (auto audioComp = Wonderhoy::m_AudioObj->GetComponent<AudioComponent>())
				audioComp->Play(0.3f);		// 음량 조절 (0.1f ~ 1.0f)

			for (size_t i = 0; i < 30; i++)
			{
				auto emuResource = ResourceManager::GetInstance().CreateBitmapResource("../Resource/WonderhoyJP.webp");
				GameObject* wonderhoyJP = m_Scene->CreateObject<GameObject>();
				m_ImageObjects.push_back(wonderhoyJP);

				auto* tr = wonderhoyJP->AddComponent<TransformComponent>();
				float randomScale = Random::Float(0.1f, 0.5f);
				tr->SetScale(randomScale, randomScale);
				tr->SetTranslation(Random::Float(-512, 512), Random::Float(-250, 250));

				auto* sr = wonderhoyJP->AddComponent<SpriteRenderComponent>();
				sr->SetBitmap(emuResource);
			}
		}

		// Erase
		if (InputSystem::GetInstance().IsKeyPressed('L'))
		{
			if (!m_ImageObjects.empty())
			{
				for (size_t i = 0; i < 30; i++)
				{
					GameObject* obj = m_ImageObjects.back();
					m_Scene->DestroyObject(obj);
					m_ImageObjects.pop_back();
				}
			}
		}

		// Clear
		if (InputSystem::GetInstance().IsKeyPressed('C'))
		{
			if (m_ImageObjects.empty()) return;

			for (auto obj : m_ImageObjects)
			{
				SceneManager::GetInstance().GetCurrentScene()->DestroyObject(obj);
			}
			m_ImageObjects.clear();
		}

		// Memory Release
		if (InputSystem::GetInstance().IsKeyPressed('T'))
		{
			// 씬 전환할때 해주는 것이 좋다.
			D2DEngineWrapper::GetInstance().m_dxgiDevice->Trim();
		}
	}

private:
	std::vector<GameObject*> m_ImageObjects;
	Scene* m_Scene = nullptr;
};