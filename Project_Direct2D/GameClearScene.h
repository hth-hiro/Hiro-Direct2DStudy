#pragma once
#include "../D2DEngine/Scene.h"

class GameClearScene : public Scene
{
public:
	GameClearScene() = default;
	virtual ~GameClearScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;
};

