#include "pch.h"
#include "ScriptSystem.h"
#include "ScriptComponent.h"

ScriptSystem::ScriptSystem()
{
}

ScriptSystem::~ScriptSystem()
{
	m_Components.clear();
}

void ScriptSystem::Awake()
{
	for (ScriptComponent* comp : m_Components)
	{
		if (comp)
		{
			comp->Awake();
		}
	}
}

void ScriptSystem::Start()
{
	for (ScriptComponent* comp : m_Components)
	{
		if (comp)
		{
			comp->Start();
		}
	}
}

void ScriptSystem::Update()
{
	for (ScriptComponent* comp : m_Components)
	{
		if (comp)
		{
			comp->Update();
		}
	}
}

void ScriptSystem::Register(ScriptComponent* comp)
{
	if (comp)
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), comp);
		if (it == m_Components.end()) {
			m_Components.push_back(comp);
		}
	}
}
void ScriptSystem::Unregister(ScriptComponent* comp)
{
	if (comp)
	{
		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());
	}
}