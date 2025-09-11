#pragma once
#include "framework.h"
#include "D2DEngineWrapper.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "ScriptSystem.h"
#include "AnimatorComponent.h"
#include "ColliderSystem.h"
//#include "AudioManager.h"

class Application
{
public:
    Application() = default;
    virtual ~Application() {}

    virtual void Initialize();
    virtual void Run();
    virtual void Update();
    virtual void Render();
    virtual void Uninitialize();

private:
    HWND                    m_hwnd = nullptr;
    HRESULT                 hr;
    HINSTANCE		        m_hInstance = nullptr;
    UINT                    m_Width = 1024;
    UINT                    m_Height = 768;

    std::wstring	        m_WindowName = L"Solar System";
    std::wstring	        m_TitleName = L"D2DEngine";
    std::string		        m_ModulePath;
    std::string		        m_WorkingPath;

    D2DEngineWrapper        m_D2DEngineWrapper;
    SceneManager            m_SceneManager;

    RenderSystem            m_RenderSystem;
    InputSystem             m_InputSystem;
    ScriptSystem            m_ScriptSystem;
    AnimatorComponent       m_Animator;
    ColliderSystem          m_ColliderSystem;
};