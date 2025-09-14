#include "PlayScene.h"

/*-----Camera-----*/
#include "../D2DEngine/Camera.h"

/*-----Components-----*/
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/TextRenderComponent.h"
#include "../D2DEngine/AudioComponent.h"

/*-----Scripts-----*/
#include "PlayInputScript.h"
#include "PlayBackgroundScript.h"
#include "PlayTextScript.h"
#include "PlayMemoryTextScript.h"
#include "Wonderhoy.h"

/*-----GameObjects-----*/
#include "UI_Text.h"
#include "UI_Button.h"

/*-----Temp-----*/
#include "ReturnButtonScript.h"
#include "SceneChangeScript.h"

void PlayScene::Enter()
{
	SetBGColor(EColor::Black);
	ObjectHandleTable::Create();

	Camera::GetInstance().Reset();
	
	// Background
	GameObject* background = CreateObject<GameObject>();
	background->AddComponent<SpriteRenderComponent>();
	background->AddComponent<PlayBackgroundScript>();

	// Audio
	GameObject* audio = CreateObject<GameObject>();
	audio->AddComponent<Wonderhoy>();

	// SceneInput
	GameObject* input = CreateObject<GameObject>();
	input->AddComponent<PlayInputScript>();
	input->AddComponent<SceneChangeScript>();

	// UI_Text
	GameObject* text = CreateObject<UI_Text>();
	text->AddComponent<TextRenderComponent>();
	text->AddComponent<PlayTextScript>();

	// UI_MemoryText
	GameObject* memory = CreateObject<UI_Text>();
	memory->AddComponent<TextRenderComponent>();
	memory->AddComponent<PlayMemoryTextScript>();

	// UI_Button
	GameObject* button = CreateObject<UI_Button>();
	button->AddComponent<ReturnButtonScript>();
	// юс╫ц

	Scene::Enter();
}

void PlayScene::Update()
{
	Scene::Update();

	Camera::GetInstance().Update();
	D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	D2DEngineWrapper::GetInstance().matCameraInv.Invert();
}