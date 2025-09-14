#include "OptionScene.h"
#include "../D2DEngine/Camera.h"
#include "SceneChangeScript.h"

void OptionScene::Enter()
{
	SetBGColor(EColor::LightBlue);
	ObjectHandleTable::Create();

	Camera::GetInstance().Reset();

	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<SceneChangeScript>();

	Scene::Enter();
}

void OptionScene::Update()
{
	Scene::Update();
}
