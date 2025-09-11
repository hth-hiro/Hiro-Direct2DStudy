#pragma once
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/AudioComponent.h"

#include "../D2DEngine/Scene.h"
#include "../D2DEngine/GameObject.h"

class Wonderhoy : public ScriptComponent
{
public:
	void Start() override
	{
		m_AudioObj = SceneManager::GetInstance().GetCurrentScene()->CreateObject<GameObject>();
		m_AudioComp = m_AudioObj->AddComponent<AudioComponent>();
		m_AudioComp->Load("Wonderhoy.mp3", AudioMode::Loop);
	}

	static GameObject* m_AudioObj;
private:
	AudioComponent* m_AudioComp;
};
