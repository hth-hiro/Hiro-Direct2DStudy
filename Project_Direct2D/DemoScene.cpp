/*
중력,속력 등의 물리적인 Simulation(Dynamic) 방식으로 이동하는 Component와
중력이 없는 임의의 코드로 움직이는 Script(Kinematic) 방식의 Component를 제작합니다.
또한 충돌 탐지(Overlap,Block)를 지원하는 Component를 제작합니다.

제작한 컴포넌트의 설명문서를 작성하고 기술데모를 프로그램을 작성합니다.
*/

/*
DynamicComponent를 통해 물리와 중력을 추가하였고,
벽과 플레이어와의 충돌, 플레이어와 바닥 간 충돌 구현
*/

// 충돌 이벤트 구현하기
// 예를 들어 불구덩이 같은 구역이 있다고 하면
// 그 특정 구역에 들어갔을 때 헬스컴포넌트로 인해서 죽는? 그런 이벤트
// 박스 콜라이더에 이미 '충돌 처리'라는 기본적인 구조가 들어있음
// 근데 그 충돌 처리라는 것을 다른 것에서는 Overlaps 될때 다른 기능을 수행할 수 있도록
// 그 기능을 나눠놓는게 좋다.
// ColliderSystem / TickDamageSystem 각자 필요에 따라 호출되는 이벤트가 다르게.

#include "DemoScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/AnimatorComponent.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/BoxColliderComponent.h"
#include "../D2DEngine/ColliderDebugRenderer.h"
#include "../D2DEngine/DynamicComponent.h"

/*-----Scripts-----*/
#include "DemoTextScript.h"
#include "AnimeRenderScript.h"
#include "PlayerMovementScript.h"
#include "DemoInputScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "UI_Button.h"

/*-----Temp-----*/
#include "ReturnButtonScript.h"

void DemoScene::Enter()
{
	SetBGColor(EColor::White);

	Camera::GetInstance().Reset();
	//D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	//D2DEngineWrapper::GetInstance().matCameraInv.Invert();

	// SceneInput
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<ColliderDebugRenderer>();
	input->AddComponent<DemoInputScript>();

	// Character_Girl
	m_Player = CreateObject<GameObject>();
	m_Player->AddComponent<SpriteRenderComponent>();
	m_Player->AddComponent<AnimatorComponent>();
	m_Player->AddComponent<AnimationController>();
	m_Player->AddComponent<AnimeRenderScript>();
	m_Player->AddComponent<BoxColliderComponent>();
	m_Player->AddComponent<ColliderDebugRenderer>();
	m_Player->AddComponent<DynamicComponent>();
	m_Player->AddComponent<PlayerMovementScript>();

	// GameObject_Ground
	GameObject* ground = CreateObject<GameObject>();
	ground->AddComponent<SpriteRenderComponent>();
	auto* groundTr = ground->GetComponent<TransformComponent>();
	groundTr->SetScale(500, 20);
	groundTr->SetTranslation(0, -200);
	// 임시 위치 세팅
	ground->AddComponent<BoxColliderComponent>();
	ground->AddComponent<ColliderDebugRenderer>();

	// GameObject_box
	GameObject* box = CreateObject<GameObject>();
	box->AddComponent<SpriteRenderComponent>();
	auto* boxTr = box->GetComponent<TransformComponent>();
	boxTr->SetScale(20, 20);
	boxTr->SetTranslation(0, -100);
	// 임시 위치 세팅
	box->AddComponent<BoxColliderComponent>();
	box->AddComponent<DynamicComponent>();
	box->AddComponent<ColliderDebugRenderer>();

	// GameObject_Fire
	GameObject* fire = CreateObject<GameObject>();
	fire->AddComponent<SpriteRenderComponent>();
	auto* fireTr = fire->GetComponent<TransformComponent>();
	fireTr->SetScale(500, 20);
	fireTr->SetTranslation(-500, -200);
	// 임시 위치 세팅
	fire->AddComponent<BoxColliderComponent>();
	fire->AddComponent<ColliderDebugRenderer>();

	// GameObject_Wall
	GameObject* wall = CreateObject<GameObject>();
	wall->AddComponent<SpriteRenderComponent>();
	auto* wallTr = wall->GetComponent<TransformComponent>();
	wallTr->SetScale(50, 500);
	wallTr->SetTranslation(150, 0);
	// 임시 위치 세팅
	wall->AddComponent<BoxColliderComponent>();
	wall->AddComponent<ColliderDebugRenderer>();

	// GameObject_Roof
	GameObject* roof = CreateObject<GameObject>();
	roof->AddComponent<SpriteRenderComponent>();
	auto* roofTr = roof->GetComponent<TransformComponent>();
	roofTr->SetScale(100, 20);
	roofTr->SetTranslation(90, 40);
	// 임시 위치 세팅
	roof->AddComponent<BoxColliderComponent>();
	roof->AddComponent<ColliderDebugRenderer>();

	GameObject* roof2 = CreateObject<GameObject>();
	roof2->AddComponent<SpriteRenderComponent>();
	auto* roof2Tr = roof2->GetComponent<TransformComponent>();
	roof2Tr->SetScale(100, 20);
	roof2Tr->SetTranslation(-100, -60);
	// 임시 위치 세팅
	roof2->AddComponent<BoxColliderComponent>();
	roof2->AddComponent<ColliderDebugRenderer>();

	// UI_Text
	GameObject* text = CreateObject<UI_Text>();
	text->AddComponent<TextRenderComponent>();
	text->AddComponent<DemoTextScript>();

	// UI_Button
	GameObject* button = CreateObject<UI_Button>();
	button->AddComponent<ReturnButtonScript>();

	Scene::Enter();
}

void DemoScene::Update()
{
	Scene::Update();
}
