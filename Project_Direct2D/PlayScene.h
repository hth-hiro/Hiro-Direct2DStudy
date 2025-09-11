#pragma once
#include "../D2DEngine/Scene.h"
#include "../D2DEngine/ObjectHandleTable.h"

class PlayScene :
    public Scene
{
public:
    PlayScene() = default;
    virtual ~PlayScene() = default;

    void Enter() override;
    void Update() override;
    void Exit() override {
        Scene::Exit(); ObjectHandleTable::Destroy();
    }
};
