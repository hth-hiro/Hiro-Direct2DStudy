#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/D2DEngineWrapper.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/GameManager.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/Time.h"

// 전역적으로 공통적으로 사용하는 디버그용 씬 전환 스크립트
// 나중에는 디버그용이 아닌 전역적으로사용하는 키 입력에 사용하도록 할듯(예를들어 ESC같은거)
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
			SceneManager::GetInstance().ChangeScene(3);				// 옵션씬 강제 이동 비활성화
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

		// 일시정지
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

			std::cout << "[Debug] 플레이 타임 : " << playTime << std::endl;
			std::cout << "[Debug] 토탈 타임 : " << totalTime << std::endl;
		}

		//if (InputSystem::GetInstance().IsKeyPressed('S'))
		//{
		//	// Data => Base64 인코딩
		//	GameManager::GetInstance().SaveGame("../Data/RGF0YQ==.json");

		//	std::cout << "[Debug] 저장되었습니다. " << std::endl;
		//}

		//if (InputSystem::GetInstance().IsKeyPressed('L'))
		//{
		//	GameManager::GetInstance().LoadGame("../Data/RGF0YQ==.json");

		//	float totalTime = Time::GetInstance().GetTotalTime();
		//	float playTime = Time::GetInstance().GetPlayTime();

		//	std::cout << GameManager::GetInstance().GetLevel() << std::endl;
		//	std::cout << "[Debug] 플레이 타임 : " << playTime << std::endl;
		//	std::cout << "[Debug] 토탈 타임 : " << totalTime << std::endl;

		//	std::cout << "[Debug] 불러오기 성공" << std::endl;
		//}
	}
};