#pragma once
#include "../D2DEngine/Scene.h"

class TutorialScene : public Scene
{
public:
	TutorialScene() = default;
	virtual ~TutorialScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;
};

