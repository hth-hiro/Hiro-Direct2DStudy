#pragma once
#include "../D2DEngine/Scene.h"

class TestScene : public Scene
{
public:
	TestScene() = default;
	virtual ~TestScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;
};

