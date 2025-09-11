#pragma once
#include "../D2DEngine/Application.h"
#include "../D2DEngine/GameObject.h"

class GameObject;
class TransformComponent;
class DemoGameApp : public Application
{
public:
    DemoGameApp() = default;
    ~DemoGameApp() = default;

    void Initialize() override;
    void Uninitialize() override;
};
