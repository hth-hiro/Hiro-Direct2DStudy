#include "TutorialScene.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "TitleBackgroundScript.h"
#include "SceneChangeScript.h"

void TutorialScene::Enter()
{
	SetBGColor(EColor::Mint);

	// Background
	GameObject* background = CreateObject<GameObject>();
	background->AddComponent<SpriteRenderComponent>();
	background->AddComponent<TitleBackgroundScript>();

	// SceneInput
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<SceneChangeScript>();

	Scene::Enter();
}

void TutorialScene::Update()
{
	__super::Update();
}
