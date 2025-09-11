#pragma once
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BoxColliderComponent.h"

class DemoScene : public Scene
{
public:
	DemoScene() = default;
	virtual ~DemoScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;

private:
	GameObject* m_Player;
	GameObject* m_Button;

	BoxColliderComponent* m_PlayerCol;
};

