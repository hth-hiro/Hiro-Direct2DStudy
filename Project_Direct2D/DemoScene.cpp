/*
�߷�,�ӷ� ���� �������� Simulation(Dynamic) ������� �̵��ϴ� Component��
�߷��� ���� ������ �ڵ�� �����̴� Script(Kinematic) ����� Component�� �����մϴ�.
���� �浹 Ž��(Overlap,Block)�� �����ϴ� Component�� �����մϴ�.

������ ������Ʈ�� �������� �ۼ��ϰ� ������� ���α׷��� �ۼ��մϴ�.
*/

/*
DynamicComponent�� ���� ������ �߷��� �߰��Ͽ���,
���� �÷��̾���� �浹, �÷��̾�� �ٴ� �� �浹 ����
*/

// �浹 �̺�Ʈ �����ϱ�
// ���� ��� �ұ����� ���� ������ �ִٰ� �ϸ�
// �� Ư�� ������ ���� �� �ｺ������Ʈ�� ���ؼ� �״�? �׷� �̺�Ʈ
// �ڽ� �ݶ��̴��� �̹� '�浹 ó��'��� �⺻���� ������ �������
// �ٵ� �� �浹 ó����� ���� �ٸ� �Ϳ����� Overlaps �ɶ� �ٸ� ����� ������ �� �ֵ���
// �� ����� �������°� ����.
// ColliderSystem / TickDamageSystem ���� �ʿ信 ���� ȣ��Ǵ� �̺�Ʈ�� �ٸ���.

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
	// �ӽ� ��ġ ����
	ground->AddComponent<BoxColliderComponent>();
	ground->AddComponent<ColliderDebugRenderer>();

	// GameObject_box
	GameObject* box = CreateObject<GameObject>();
	box->AddComponent<SpriteRenderComponent>();
	auto* boxTr = box->GetComponent<TransformComponent>();
	boxTr->SetScale(20, 20);
	boxTr->SetTranslation(0, -100);
	// �ӽ� ��ġ ����
	box->AddComponent<BoxColliderComponent>();
	box->AddComponent<DynamicComponent>();
	box->AddComponent<ColliderDebugRenderer>();

	// GameObject_Fire
	GameObject* fire = CreateObject<GameObject>();
	fire->AddComponent<SpriteRenderComponent>();
	auto* fireTr = fire->GetComponent<TransformComponent>();
	fireTr->SetScale(500, 20);
	fireTr->SetTranslation(-500, -200);
	// �ӽ� ��ġ ����
	fire->AddComponent<BoxColliderComponent>();
	fire->AddComponent<ColliderDebugRenderer>();

	// GameObject_Wall
	GameObject* wall = CreateObject<GameObject>();
	wall->AddComponent<SpriteRenderComponent>();
	auto* wallTr = wall->GetComponent<TransformComponent>();
	wallTr->SetScale(50, 500);
	wallTr->SetTranslation(150, 0);
	// �ӽ� ��ġ ����
	wall->AddComponent<BoxColliderComponent>();
	wall->AddComponent<ColliderDebugRenderer>();

	// GameObject_Roof
	GameObject* roof = CreateObject<GameObject>();
	roof->AddComponent<SpriteRenderComponent>();
	auto* roofTr = roof->GetComponent<TransformComponent>();
	roofTr->SetScale(100, 20);
	roofTr->SetTranslation(90, 40);
	// �ӽ� ��ġ ����
	roof->AddComponent<BoxColliderComponent>();
	roof->AddComponent<ColliderDebugRenderer>();

	GameObject* roof2 = CreateObject<GameObject>();
	roof2->AddComponent<SpriteRenderComponent>();
	auto* roof2Tr = roof2->GetComponent<TransformComponent>();
	roof2Tr->SetScale(100, 20);
	roof2Tr->SetTranslation(-100, -60);
	// �ӽ� ��ġ ����
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
