#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/NewButtonComponent.h"
#include "../D2DEngine/ResourceManager.h"

#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/SceneManager.h"

class TitleButtonScript : public ScriptComponent
{
public:
	void Start() override
	{
		CreateButton(L"�����ϱ�", 400, 300, 200, 100, [this]() { StartNewGame(); });
		CreateButton(L"�̾��ϱ�", 400, 420, 200, 100, [this]() { ContinueGame(); });
		CreateButton(L"ȯ�漳��", 400, 540, 200, 100, [this]() { OptionScene(); });
		CreateButton(L"ũ����", 400, 660, 200, 100, [this]() { ShowCredits(); });
		CreateButton(L"���� ����", 400, 780, 200, 100, [this]() { ExitGame(); });
	}

private:
	void CreateButton(const std::wstring& name, int x, int y, int width, int height, std::function<void()> onClick)
	{
		
		auto* scene = owner->GetScene();
		GameObject* btnObj = scene->CreateObject<GameObject>();
		auto* button = btnObj->AddComponent<NewButtonComponent>();

		std::unordered_map<EButtonState, std::shared_ptr<BitmapResource>> bitmaps;

		bitmaps[EButtonState::Normal] = ResourceManager::GetInstance().CreateBitmapResource("../Resource/UI/button.png");
		bitmaps[EButtonState::Hovered] = ResourceManager::GetInstance().CreateBitmapResource("../Resource/UI/button.png");
		bitmaps[EButtonState::Pressed] = ResourceManager::GetInstance().CreateBitmapResource("../Resource/UI/button.png");

		RECT rect = { x, y, x + width, y + height };
		button->Create(btnObj, bitmaps, rect);

		button->SetOnClick(onClick);
	}

	void StartNewGame() { SceneManager::GetInstance().ChangeScene(EScene::Tutorial); }
	void ContinueGame() {std::cout << "�̾��ϱ� ����" << std::endl; }
	void OptionScene() { SceneManager::GetInstance().ChangeScene(EScene::Option); }
	void ShowCredits() { std::cout << "������ : ��" << std::endl; }
	void ExitGame() { PostQuitMessage(0); }


};