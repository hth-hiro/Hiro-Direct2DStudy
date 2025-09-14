#include "GameClearScene.h"
#include "../D2DEngine/Camera.h"
#include "SceneChangeScript.h"

void GameClearScene::Enter()
{
	SetBGColor(EColor::LightOrange);
	ObjectHandleTable::Create();

	Camera::GetInstance().Reset();

	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<SceneChangeScript>();

	Scene::Enter();
}

void GameClearScene::Update()
{
	Scene::Update();
}
