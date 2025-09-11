#pragma once
#include "pch.h"
#include "AnimationController.h"

using json = nlohmann::json;

class AnimationBaseState
{
public:
	virtual ~AnimationBaseState() = default;

	virtual void Enter(AnimationController* controller) = 0;
	virtual void Update(AnimationController* controller) = 0;
	virtual void Exit(AnimationController* controller) {}
	virtual const std::string& GetName() const = 0;
};

