#include "pch.h"
#include "Scene.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"   //

void Scene::Clear()
{
	for (auto& object : m_Objects)
	{
		delete object;
	}
	m_Objects.clear();

    if(D2DEngineWrapper::GetInstance().m_dxgiDevice)
        D2DEngineWrapper::GetInstance().m_dxgiDevice->Trim();
}

void Scene::Enter()
{
    for (auto& object : m_Objects)
    {
        object->Awake();
    }

    ScriptSystem::GetInstance().Awake();

    for (auto& object : m_Objects)
    {
        object->Start();
    }

    ScriptSystem::GetInstance().Start();
}

void Scene::Update()
{
    // Delete
    for (auto it = m_Objects.begin(); it != m_Objects.end(); )
    {
        if ((*it)->m_IsDead)
        {
            delete* it;
            it = m_Objects.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (!tmpObj.empty())
    {
        for (auto& object : tmpObj)
        {
            m_Objects.push_back(object);
            object->Awake();
            object->Start();
        }
        tmpObj.clear();
    }

    for (auto& object : m_Objects)
    {
        object->Update();
    }
}

void Scene::Render()
{
    //RenderSystem::Instance().Render();

	//for (auto& object : m_Objects)
	//{
 //       if (!object->isUI())
 //       {
	//	    object->Render();
 //       }
 //       else
 //       {
 //           object->Render();
 //       }
	//}
}
