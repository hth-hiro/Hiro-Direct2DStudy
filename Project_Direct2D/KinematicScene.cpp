/*
중력,속력 등의 물리적인 Simulation(Dynamic) 방식으로 이동하는 Component와
중력이 없는 임의의 코드로 움직이는 Script(Kinematic) 방식의 Component를 제작합니다.
또한 충돌 탐지(Overlap,Block)를 지원하는 Component를 제작합니다.

제작한 컴포넌트의 설명문서를 작성하고 기술데모를 프로그램을 작성합니다.
*/

/*
KinematicComponent를 통해 물리를 추가하였고,
벽과 플레이어와의 충돌, 플레이어와 바닥 간 충돌 구현
*/

#include "KinematicScene.h"

#include "DemoScene.h"

#include "../D2DEngine/GameObject.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/AnimatorComponent.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/BoxColliderComponent.h"
#include "../D2DEngine/ColliderDebugRenderer.h"
#include "../D2DEngine/KinematicComponent.h"

/*-----Scripts-----*/
#include "KinematicTextScript.h"
#include "AnimeRenderScript.h"
#include "PlayerKinematicScript.h"
#include "DemoInputScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "UI_Button.h"

/*-----Temp-----*/
#include "ReturnButtonScript.h"

void KinematicScene::Enter()
{
	SetBGColor(D2D1::ColorF::Green);

	Camera::GetInstance().Reset();
	D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	D2DEngineWrapper::GetInstance().matCameraInv.Invert();

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
	m_Player->AddComponent<KinematicComponent>();
	m_Player->AddComponent<PlayerKinematicScript>();

	// GameObject_Wall
	GameObject* wall = CreateObject<GameObject>();
	wall->AddComponent<SpriteRenderComponent>();
	auto* wallTr = wall->GetComponent<TransformComponent>();
	wallTr->SetScale(50, 500);
	wallTr->SetTranslation(150, 0);
	// 임시 위치 세팅
	wall->AddComponent<BoxColliderComponent>();
	wall->AddComponent<KinematicComponent>();
	wall->AddComponent<ColliderDebugRenderer>();

	// UI_Text
	GameObject* text = CreateObject<UI_Text>();
	text->AddComponent<TextRenderComponent>();
	text->AddComponent<KinematicTextScript>();

	Scene::Enter();
}

void KinematicScene::Update()
{
	Scene::Update();
}
