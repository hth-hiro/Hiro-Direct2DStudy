#pragma once
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/BoxColliderComponent.h"

class GameObject;
class KinematicScene : public Scene
{
public:
	KinematicScene() = default;
	virtual ~KinematicScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;

private:
	GameObject* m_Player;
	GameObject* m_Button;

	BoxColliderComponent* m_PlayerCol;
};

