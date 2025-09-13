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

	// �� �κ��� �׽�Ʈ��
	SceneManager::GetInstance().CreateScene<AnimeScene>(L"Anime");
	SceneManager::GetInstance().CreateScene<DemoScene>(L"Demo");
	SceneManager::GetInstance().CreateScene<KinematicScene>(L"Kinematic");
	SceneManager::GetInstance().CreateScene<TestScene>(L"TestScene");

	// real gameProject(6������ ������ ��, ���߿� �̰� 0�������� �Ұ���)
	SceneManager::GetInstance().CreateScene<TitleScene>(L"TitleScene");
	SceneManager::GetInstance().CreateScene<TutorialScene>(L"TutorialScene");
	SceneManager::GetInstance().CreateScene<PlayScene>(L"PlayScene");
	SceneManager::GetInstance().CreateScene<OptionScene>(L"OptionScene");
	SceneManager::GetInstance().CreateScene<GameClearScene>(L"GameClearScene");
	SceneManager::GetInstance().CreateScene<GameOverScene>(L"GameOverScene");

	//SceneManager::GetInstance().CreateScene<>

	SceneManager::GetInstance().ChangeScene(0);
}

void DemoGameApp::Uninitialize()
{
	__super::Uninitialize();
}
