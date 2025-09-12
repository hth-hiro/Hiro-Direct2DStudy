#include "TestScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"

/*-----Scripts-----*/
#include "PlayerMovementScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "../D2DEngine/AnimatorComponent.h"
#include "AnimeRenderScript.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/BoxColliderComponent.h"
#include "../D2DEngine/ColliderDebugRenderer.h"
#include "../D2DEngine/DynamicComponent.h"

void TestScene::Enter()
{
	SetBGColor(EColor::LightBlue);

	Camera::GetInstance().Reset();
	
	auto background = CreateObject<GameObject>();
	background->AddComponent<SpriteRenderComponent>();

	// Character_Girl
	auto player = CreateObject<GameObject>();
	player->AddComponent<SpriteRenderComponent>();
	player->AddComponent<AnimatorComponent>();
	player->AddComponent<AnimationController>();
	player->AddComponent<AnimeRenderScript>();
	player->AddComponent<BoxColliderComponent>();
	player->AddComponent<ColliderDebugRenderer>();
	player->AddComponent<DynamicComponent>();
	player->AddComponent<PlayerMovementScript>();

	// GameObject_Ground
	GameObject* ground = CreateObject<GameObject>();
	ground->AddComponent<SpriteRenderComponent>();
	auto* groundTr = ground->GetComponent<TransformComponent>();
	groundTr->SetScale(500, 20);
	groundTr->SetTranslation(0, -200);
	// 임시 위치 세팅
	ground->AddComponent<BoxColliderComponent>();
	ground->AddComponent<ColliderDebugRenderer>();

	Scene::Enter();
}

void TestScene::Update()
{
	Scene::Update();
}
