#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/SceneManager.h"

class AnimeInputScript : public ScriptComponent
{
public:
	void Update() override
	{
		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			SceneManager::GetInstance().ChangeScene(1);
		}

		if (InputSystem::GetInstance().IsKeyPressed(VK_SPACE))
		{
			SceneManager::GetInstance().ChangeScene(3);
		}
	}
};