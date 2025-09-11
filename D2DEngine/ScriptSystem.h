#pragma once
#include <vector>
#include "Singleton.h"

class ScriptComponent;
class ScriptSystem : public Singleton<ScriptSystem>
{
private:

public:
	ScriptSystem();
	virtual ~ScriptSystem();
	std::vector<ScriptComponent*> m_Components;

	void Awake();
	void Start();
	void Update();
	void Register(ScriptComponent* comp);
	void Unregister(ScriptComponent* comp);
};

