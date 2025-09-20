#pragma once
#include <vector>
#include "Singleton.h"

class RenderComponent;
class UIComponent;
class RenderSystem : public Singleton<RenderSystem>
{
private:

public:
	RenderSystem() {}
	virtual ~RenderSystem() {}
	std::vector<RenderComponent*> m_Components;
	std::vector<UIComponent*> m_UIComponents;

	void Render();
	void Register(RenderComponent* comp);
	void Register(UIComponent* comp);

	void Unregister(RenderComponent* comp);
	void Unregister(UIComponent* comp);
};