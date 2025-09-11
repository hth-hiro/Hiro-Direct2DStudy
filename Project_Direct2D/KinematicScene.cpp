/*
�߷�,�ӷ� ���� �������� Simulation(Dynamic) ������� �̵��ϴ� Component��
�߷��� ���� ������ �ڵ�� �����̴� Script(Kinematic) ����� Component�� �����մϴ�.
���� �浹 Ž��(Overlap,Block)�� �����ϴ� Component�� �����մϴ�.

������ ������Ʈ�� �������� �ۼ��ϰ� ������� ���α׷��� �ۼ��մϴ�.
*/

/*
KinematicComponent�� ���� ������ �߰��Ͽ���,
���� �÷��̾���� �浹, �÷��̾�� �ٴ� �� �浹 ����
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
	// �ӽ� ��ġ ����
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
