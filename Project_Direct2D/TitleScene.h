#pragma once
#include "../D2DEngine/Scene.h"

class TitleScene :
	public Scene
{
public:
	TitleScene() = default;
	virtual ~TitleScene() = default;

	void Enter() override;
	void Exit() override { Scene::Exit(); }
	void Update() override;
};