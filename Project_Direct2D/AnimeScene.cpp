#include "AnimeScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/AnimatorComponent.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/KinematicComponent.h"

/*-----Scripts-----*/
#include "AnimeTextScript.h"
#include "AnimeRenderScript.h"
#include "AnimeInputScript.h"
#include "PlayerTransformScript.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "UI_Button.h"

/*-----Temp-----*/
#include "ReturnButtonScript.h"

void AnimeScene::Enter()
{
	SetBGColor(D2D1::ColorF::Black);

	Camera::GetInstance().Reset();
	//D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	//D2DEngineWrapper::GetInstance().matCameraInv.Invert();

	// Scene �ȿ��� Ű �Է��� ���
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<AnimeInputScript>();

	// Character_Girl
	m_Player = CreateObject<GameObject>();
	m_Player->AddComponent<SpriteRenderComponent>();
	m_Player->AddComponent<AnimatorComponent>();
	m_Player->AddComponent<AnimationController>();
	m_Player->AddComponent<AnimeRenderScript>();
	//m_Player->AddComponent<KinematicComponent>();
	m_Player->AddComponent<PlayerTransformScript>();

	// UI_Text
	GameObject* text = CreateObject<UI_Text>();
	text->AddComponent<TextRenderComponent>();
	text->AddComponent<AnimeTextScript>();

	// UI_Button
	GameObject* button = CreateObject<UI_Button>();
	button->AddComponent<ReturnButtonScript>();
	// ���� UIManager ���� ����, ��ũ��Ʈ �̸� ���� ����
	// Delegate ��� ����, AddComponent ���� Ȯ�� ���

	Scene::Enter();
}

void AnimeScene::Update()
{
	Scene::Update();

	Camera::GetInstance().Update();
	D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	D2DEngineWrapper::GetInstance().matCameraInv.Invert();
}