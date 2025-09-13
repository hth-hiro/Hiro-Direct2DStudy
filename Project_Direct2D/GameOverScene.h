#pragma once
#include "../D2DEngine/Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene() = default;
	virtual ~GameOverScene() = default;

	void Enter() override;
	void Exit() { Scene::Exit(); }
	void Update() override;
};

