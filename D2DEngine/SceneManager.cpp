#include "pch.h"
#include "SceneManager.h"

bool g_PendingSceneClear = false;

void SceneManager::StartUp()
{
}

void SceneManager::ShutDown()
{
	for (auto& scene : m_vScenes)
	{
		delete scene;
	}
	m_vScenes.clear();
}

void SceneManager::Update()
{
	if (m_nextScene)
	{
		if (m_currentScene)
			m_currentScene->Exit();
		
		if (g_PendingSceneClear)
		{
			m_currentScene = m_nextScene;
			m_nextScene = nullptr;
			g_PendingSceneClear = false;
		}

		m_currentScene->Enter();
	}

	if (m_currentScene)
		m_currentScene->Update();
}

void SceneManager::Render()
{
	if (m_currentScene)
	{
		D2DEngineWrapper::GetInstance().Clear(m_currentScene->GetBGColor());
		m_currentScene->Render();
	}
}

void SceneManager::ChangeScene(size_t index)
{
	if (index >= m_vScenes.size())
		return;

	g_PendingSceneClear = true;

	m_prevScene = m_currentScene;

	m_nextScene = m_vScenes[index];
}
