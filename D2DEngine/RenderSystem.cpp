#include "pch.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "UIComponent.h"
#include "D2DEngineWrapper.h"

void RenderSystem::Render()
{
	for (RenderComponent* comp : m_Components)
	{
		if (comp)
		{
			comp->Render();
		}
	}

	for (UIComponent* UIcomp : m_UIComponents)
	{
		if (UIcomp)
		{
			UIcomp->Render();
		}
	}
}

void RenderSystem::Register(RenderComponent* comp)
{
	if (comp)
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), comp);
		// 목록에 없으면 추가
		if (it == m_Components.end()) {
			m_Components.push_back(comp);
		}
	}
}

void RenderSystem::Register(UIComponent* comp)
{
	if (comp)
	{
		auto it = std::find(m_UIComponents.begin(), m_UIComponents.end(), comp);
		// 목록에 없으면 추가
		if (it == m_UIComponents.end()) {
			m_UIComponents.push_back(comp);
		}
	}
}

void RenderSystem::Unregister(RenderComponent* comp)
{
	if (comp)
	{
		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());
	}
}

void RenderSystem::Unregister(UIComponent* comp)
{
	if (comp)
	{
		m_UIComponents.erase(std::remove(m_UIComponents.begin(), m_UIComponents.end(), comp), m_UIComponents.end());
	}
}