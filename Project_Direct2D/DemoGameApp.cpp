#include "DemoGameApp.h"
#include "../D2DEngine/SceneManager.h"

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

	SceneManager::GetInstance().CreateScene<TitleScene>(L"Title_");
	SceneManager::GetInstance().CreateScene<PlayScene>(L"Play");
	SceneManager::GetInstance().CreateScene<AnimeScene>(L"Anime");
	SceneManager::GetInstance().CreateScene<DemoScene>(L"Demo");
	SceneManager::GetInstance().CreateScene<KinematicScene>(L"Kinematic");

	// real gameProject
	SceneManager::GetInstance().CreateScene<TitleScene>(L"TitleScene");
	SceneManager::GetInstance().CreateScene<TutorialScene>(L"TutorialScene");
	SceneManager::GetInstance().CreateScene<PlayScene>(L"PlayScene");
	SceneManager::GetInstance().CreateScene<OptionScene>(L"OptionScene");
	SceneManager::GetInstance().CreateScene<GameClearScene>(L"GameClearScene");
	SceneManager::GetInstance().CreateScene<GameOverScene>(L"GameOverScene");

	SceneManager::GetInstance().CreateScene<TestScene>(L"TestScene");
	// 여기 씬에서 애니메이션 체크해볼 것 OK
	
	//SceneManager::GetInstance().CreateScene<>

	SceneManager::GetInstance().ChangeScene(6);
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}
