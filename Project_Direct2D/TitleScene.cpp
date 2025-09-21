#include "TitleScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/UIComponent.h"

/*-----Scripts-----*/
#include "TitleInputScript.h"
#include "TitleBackgroundScript.h"
#include "TitleTextScript.h"
#include "TitleButtonScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "SceneChangeScript.h"

void TitleScene::Enter()
{
	SetBGColor(EColor::White);

	Camera::GetInstance().Reset();
	
	// Background, Title Text(Sprite)
	GameObject* background = CreateObject<GameObject>();
	background->AddComponent<SpriteRenderComponent>();
	background->AddComponent<TitleBackgroundScript>();

	// UI_Button
	GameObject* UIButton = CreateObject<GameObject>();
	UIButton->AddComponent<TitleButtonScript>();

	// SceneInput
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<TitleInputScript>();
	input->AddComponent<SceneChangeScript>();

	// UI_Text
	GameObject* text = CreateObject<UI_Text>();
	text->AddComponent<TextRenderComponent>();
	text->AddComponent<TitleTextScript>();

	Scene::Enter();
}

void TitleScene::Update()
{
	Scene::Update();
}