#include "TutorialScene.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "TitleBackgroundScript.h"

void TutorialScene::Enter()
{
	SetBGColor(EColor::White);

	// Background
	GameObject* background = CreateObject<GameObject>();
	background->AddComponent<SpriteRenderComponent>();
	background->AddComponent<TitleBackgroundScript>();

	Scene::Enter();
}

void TutorialScene::Update()
{
	__super::Update();
}
