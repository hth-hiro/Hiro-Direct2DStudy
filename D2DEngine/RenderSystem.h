#pragma once
#include <vector>
#include "Singleton.h"

class RenderComponent;
class RenderSystem : public Singleton<RenderSystem>
{
private:

public:
	RenderSystem() {}
	virtual ~RenderSystem() {}
	std::vector<RenderComponent*> m_Components;

	void Render();
	void Register(RenderComponent* comp);
	void Unregister(RenderComponent* comp);
};