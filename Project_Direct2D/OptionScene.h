#pragma once
#include "../D2DEngine/Scene.h"

class OptionScene : public Scene
{
public:
	OptionScene() = default;
	virtual ~OptionScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;
};

