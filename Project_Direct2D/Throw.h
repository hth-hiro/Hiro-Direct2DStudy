#pragma once
#include "../D2DEngine/AnimationBaseState.h"

class Throw : public AnimationBaseState
{
	void Enter(AnimationController* controller) override;
	void Update(AnimationController* controller) override;
	const std::string& GetName() const override { return name; }

private:
	std::string name = "Throw";
};

