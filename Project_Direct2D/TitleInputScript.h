#pragma once
#include "../D2DEngine/D2DEngineWrapper.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/SceneManager.h"

class TitleInputScript : public ScriptComponent
{
public:
	void Update() override
	{
		if (InputSystem::GetInstance().IsKeyPressed(VK_SPACE) ||
			InputSystem::GetInstance().IsKeyPressed(VK_RETURN))
		{
			SceneManager::GetInstance().ChangeScene(1);
		}

		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			D2DEngineWrapper::GetInstance().m_Quit = true;
		}
	}
};

