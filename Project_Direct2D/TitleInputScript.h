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
		// Debug
		if (InputSystem::GetInstance().IsKeyPressed('1'))
		{ 
			SceneManager::GetInstance().ChangeScene(1);
		}

		// �Ͻ�����
		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			//D2DEngineWrapper::GetInstance().m_Quit = true;
			if (!Time::GetInstance().isPaused())
			{
				Time::GetInstance().Pause();
				std::cout << "[Debug] �Ͻ�����" << std::endl;
			}
			else
			{
				Time::GetInstance().Resume();
				std::cout << "[Debug] �Ͻ����� ����" << std::endl;
			}
		}

		// Debug
		if (InputSystem::GetInstance().IsKeyPressed('T'))
		{
			float totalTime = Time::GetInstance().GetTotalTime();
			float playTime = Time::GetInstance().GetPlayTime();

			std::cout << "[Debug] �÷��� Ÿ�� : " <<  playTime << std::endl;
			std::cout << "[Debug] ��Ż Ÿ�� : " << totalTime << std::endl;
		}

		if (InputSystem::GetInstance().IsKeyPressed('S'))
		{
			// Data => Base64 ���ڵ�
			GameManager::GetInstance().SaveGame("../Data/RGF0YQ==.json");

			std::cout << "[Debug] ����Ǿ����ϴ�. " << std::endl;
		}

		if (InputSystem::GetInstance().IsKeyPressed('L'))
		{
			GameManager::GetInstance().LoadGame("../Data/RGF0YQ==.json");

			float totalTime = Time::GetInstance().GetTotalTime();
			float playTime = Time::GetInstance().GetPlayTime();

			std::cout << GameManager::GetInstance().GetLevel() << std::endl;
			std::cout << "[Debug] �÷��� Ÿ�� : " << playTime << std::endl;
			std::cout << "[Debug] ��Ż Ÿ�� : " << totalTime << std::endl;

			std::cout << "[Debug] �ҷ����� ����" << std::endl;
		}
	}
};

