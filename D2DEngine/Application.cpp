#include "pch.h"
#include "Application.h"
#include "RenderSystem.h"
#include "AudioManager.h"
#include "Time.h"
#include "AnimatorComponent.h"

GameObject* obj;

void Application::Initialize()
{
	hr = CoInitialize(nullptr);
	m_D2DEngineWrapper.Initialize();
	AudioManager::GetInstance().Initialize();
	Time::GetInstance().Initialize();
}

void Application::Run()
{
	MSG msg = {};

	while (!D2DEngineWrapper::GetInstance().m_Quit)
	{
		// 메시지가 있으면 처리
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Update();
		Render();
	}
}

void Application::Update()
{
	m_SceneManager.Update();
	m_InputSystem.Update();
	m_Animator.Update();
	AudioManager::GetInstance().Update();
	Time::GetInstance().Update();
	m_ScriptSystem.Update();
	m_ColliderSystem.Update();
}

void Application::Render()
{
	m_D2DEngineWrapper.BeginDraw();
	m_SceneManager.Render();
	m_RenderSystem.Render();
	m_D2DEngineWrapper.EndDraw();
}

void Application::Uninitialize()
{
	m_D2DEngineWrapper.Uninitialize();
	m_SceneManager.ShutDown();
	AudioManager::GetInstance().Uninitialize();
	CoUninitialize();

	delete obj;
}
