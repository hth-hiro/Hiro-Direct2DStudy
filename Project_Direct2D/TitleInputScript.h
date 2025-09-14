#pragma once
#include "../D2DEngine/D2DEngineWrapper.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/GameManager.h"
#include "../D2DEngine/Time.h"

class TitleInputScript : public ScriptComponent
{
public:
	void Update() override
	{
		if (InputSystem::GetInstance().IsKeyPressed('S'))
		{
			// Data => Base64 인코딩
			GameManager::GetInstance().SaveGame("../Data/RGF0YQ==.json");

			std::cout << "[Debug] 저장되었습니다. " << std::endl;
		}

		if (InputSystem::GetInstance().IsKeyPressed('L'))
		{
			GameManager::GetInstance().LoadGame("../Data/RGF0YQ==.json");

			float totalTime = Time::GetInstance().GetTotalTime();
			float playTime = Time::GetInstance().GetPlayTime();

			std::cout << GameManager::GetInstance().GetLevel() << std::endl;
			std::cout << "[Debug] 플레이 타임 : " << playTime << std::endl;
			std::cout << "[Debug] 토탈 타임 : " << totalTime << std::endl;

			std::cout << "[Debug] 불러오기 성공" << std::endl;
		}
	}
};

