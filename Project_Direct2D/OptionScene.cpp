#include "OptionScene.h"
#include "../D2DEngine/Camera.h"
#include "SceneChangeScript.h"
#include "OptionButtonScript.h"

void OptionScene::Enter()
{
	SetBGColor(EColor::LightBlue);
	ObjectHandleTable::Create();

	Camera::GetInstance().Reset();

	// SceneInput
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<SceneChangeScript>();

	GameObject* UIButton = CreateObject<GameObject>();
	UIButton->AddComponent<OptionButtonScript>();

	Scene::Enter();
}

void OptionScene::Update()
{
	Scene::Update();
}
