#pragma once
#include "../D2DEngine/AnimatorComponent.h"
#include "../D2DEngine/AnimationBaseState.h"
#include "../D2DEngine/AnimationController.h"

class IdleState : public AnimationBaseState
{
public:
	void Enter(AnimationController* controller) override;
	void Update(AnimationController* controller) override;
	const std::string& GetName() const override { return name; }

private:
	std::string name = "Idle";
};