#include "GameOverScene.h"
#include "../D2DEngine/Camera.h"
#include "SceneChangeScript.h"

void GameOverScene::Enter()
{
	SetBGColor(EColor::LightPink);
	ObjectHandleTable::Create();

	Camera::GetInstance().Reset();

	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<SceneChangeScript>();

	Scene::Enter();
}

void GameOverScene::Update()
{
	Scene::Update();
}
