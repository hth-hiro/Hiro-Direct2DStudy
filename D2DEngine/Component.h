#pragma once
#include <iostream>
#include "Object.h"

class GameObject;
class Scene;
class Component : public Object
{
public:
	virtual ~Component() = default;
	GameObject* owner = nullptr;
	Scene* scene = nullptr;

	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void OnEnable() = 0;
	virtual void OnDestroy() = 0;
};