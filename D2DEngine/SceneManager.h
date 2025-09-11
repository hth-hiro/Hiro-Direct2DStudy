#pragma once
#include <memory>
#include "Scene.h"
#include "D2DEngineWrapper.h"
#include "Singleton.h"
#include "Camera.h"

class Scene;
class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	std::vector<Scene*> m_vScenes;

	void StartUp();
	void ShutDown();
	void Update(); 
	void Render();

	// Set
	void ChangeScene(size_t index);

	int GetCurrentSceneIndex()
	{
		for (size_t i = 0; i < m_vScenes.size(); ++i)
		{
			if (m_vScenes[i] == m_currentScene)
				return static_cast<int>(i);
		}
		return -1;
	}

	std::wstring GetCurrentSceneByName()
	{
		return m_SceneName;
	}

	Scene* GetCurrentScene() { return m_currentScene; }

	template<typename T>
	void CreateScene(std::wstring sceneName)
	{
		Scene* scene = new T();
		m_vScenes.push_back(scene);
		m_SceneName = sceneName;
	}

private:
	Scene* m_currentScene = nullptr;
	Scene* m_nextScene = nullptr;

	std::wstring m_SceneName;
};

