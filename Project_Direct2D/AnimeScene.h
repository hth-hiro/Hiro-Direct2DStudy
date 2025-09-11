#pragma once
#include "../D2DEngine/Scene.h"

class AnimeScene :
	public Scene
{
public:
	AnimeScene() = default;
	virtual ~AnimeScene() = default;

	void Enter() override;
	void Update() override;
	void Exit() override { Scene::Exit(); }

private:
	GameObject* m_Player;
};