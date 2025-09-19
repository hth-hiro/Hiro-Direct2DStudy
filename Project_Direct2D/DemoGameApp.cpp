#include "DemoGameApp.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/InputSystem.h"

#include "TitleScene.h"
#include "PlayScene.h"
#include "AnimeScene.h"
#include "DemoScene.h"
#include "KinematicScene.h"
#include "TestScene.h"
#include "TutorialScene.h"
#include "OptionScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"

void DemoGameApp::Initialize()
{
	__super::Initialize();

	// real gameProject
	SceneManager::GetInstance().CreateScene<TitleScene>(L"TitleScene");			// 0
	SceneManager::GetInstance().CreateScene<TutorialScene>(L"TutorialScene");	// 1
	SceneManager::GetInstance().CreateScene<PlayScene>(L"PlayScene");			// 2
	SceneManager::GetInstance().CreateScene<OptionScene>(L"OptionScene");		// 3
	SceneManager::GetInstance().CreateScene<GameClearScene>(L"GameClearScene");	// 4
	SceneManager::GetInstance().CreateScene<GameOverScene>(L"GameOverScene");	// 5

	// 이 부분은 테스트씬 (6 ~ 9)
	SceneManager::GetInstance().CreateScene<AnimeScene>(L"Anime");
	SceneManager::GetInstance().CreateScene<DemoScene>(L"Demo");
	SceneManager::GetInstance().CreateScene<KinematicScene>(L"Kinematic");
	SceneManager::GetInstance().CreateScene<TestScene>(L"TestScene");

	//SceneManager::GetInstance().CreateScene<>

	SceneManager::GetInstance().ChangeScene(0);
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}
