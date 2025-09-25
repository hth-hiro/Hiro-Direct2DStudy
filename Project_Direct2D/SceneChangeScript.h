#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/D2DEngineWrapper.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/GameManager.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/Time.h"

// ���������� ���������� ����ϴ� ����׿� �� ��ȯ ��ũ��Ʈ
// ���߿��� ����׿��� �ƴ� ���������λ���ϴ� Ű �Է¿� ����ϵ��� �ҵ�(������� ESC������)
class SceneChangeScript : public ScriptComponent
{
public:
	void Update() override
	{
		// Debug
		if (InputSystem::GetInstance().IsKeyPressed('0'))
		{
			SceneManager::GetInstance().ChangeScene(EScene::Title);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('1'))
		{
			SceneManager::GetInstance().ChangeScene(EScene::Tutorial);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('2'))
		{
			SceneManager::GetInstance().ChangeScene(EScene::Play);
		}
		/*else if (InputSystem::GetInstance().IsKeyPressed('3'))
		{
			SceneManager::GetInstance().ChangeScene(3);				// �ɼǾ� ���� �̵� ��Ȱ��ȭ
		}*/
		else if (InputSystem::GetInstance().IsKeyPressed('4'))
		{
			SceneManager::GetInstance().ChangeScene(EScene::GameClear);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('5'))
		{
			SceneManager::GetInstance().ChangeScene(EScene::GameOver);
		}

		// Test
		else if (InputSystem::GetInstance().IsKeyPressed('6'))
		{
			SceneManager::GetInstance().ChangeScene(6);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('7'))
		{
			SceneManager::GetInstance().ChangeScene(7);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('8'))
		{
			SceneManager::GetInstance().ChangeScene(8);
		}
		else if (InputSystem::GetInstance().IsKeyPressed('9'))
		{
			SceneManager::GetInstance().ChangeScene(9);
		}

		// �Ͻ�����
		if (InputSystem::GetInstance().IsKeyPressed(VK_ESCAPE))
		{
			//D2DEngineWrapper::GetInstance().m_Quit = true;
			if (!Time::GetInstance().isPaused())
			{
				Time::GetInstance().Pause();
				SceneManager::GetInstance().ChangeScene(EScene::Option);
			}
			else
			{
				Time::GetInstance().Resume();				
				SceneManager::GetInstance().ChangeScene(SceneManager::GetInstance().GetPrevSceneIndex());
			}
		}

		// Debug
		if (InputSystem::GetInstance().IsKeyPressed('T'))
		{
			float totalTime = Time::GetInstance().GetTotalTime();
			float playTime = Time::GetInstance().GetPlayTime();

			std::cout << "[Debug] �÷��� Ÿ�� : " << playTime << std::endl;
			std::cout << "[Debug] ��Ż Ÿ�� : " << totalTime << std::endl;
		}

		//if (InputSystem::GetInstance().IsKeyPressed('S'))
		//{
		//	// Data => Base64 ���ڵ�
		//	GameManager::GetInstance().SaveGame("../Data/RGF0YQ==.json");

		//	std::cout << "[Debug] ����Ǿ����ϴ�. " << std::endl;
		//}

		//if (InputSystem::GetInstance().IsKeyPressed('L'))
		//{
		//	GameManager::GetInstance().LoadGame("../Data/RGF0YQ==.json");

		//	float totalTime = Time::GetInstance().GetTotalTime();
		//	float playTime = Time::GetInstance().GetPlayTime();

		//	std::cout << GameManager::GetInstance().GetLevel() << std::endl;
		//	std::cout << "[Debug] �÷��� Ÿ�� : " << playTime << std::endl;
		//	std::cout << "[Debug] ��Ż Ÿ�� : " << totalTime << std::endl;

		//	std::cout << "[Debug] �ҷ����� ����" << std::endl;
		//}
	}
};