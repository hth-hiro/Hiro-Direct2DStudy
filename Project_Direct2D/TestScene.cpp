#include "TestScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"

/*-----Scripts-----*/
#include "TitleInputScript.h"
#include "TitleBackgroundScript.h"
#include "TitleTextScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"

void TestScene::Enter()
{
	SetBGColor(EColor::LightBlue);

	Camera::GetInstance().Reset();
	
	//auto background = CreateObject<GameObject>();
	//background->AddComponent<SpriteRenderComponent>();
}

void TestScene::Update()
{
}
