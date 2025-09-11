#include "IdleState.h"
#include "AnimeRenderScript.h"

void IdleState::Enter(AnimationController* controller)
{
	auto* animator = controller->GetAnimator();
	if (animator)
		animator->SetAnimationClip(&AnimeRenderScript::idleClip);
}

void IdleState::Update(AnimationController* controller)
{
	float velocityX = std::abs(controller->GetFloat("velocityX"));
	float velocityY = std::abs(controller->GetFloat("velocityY"));

	if (controller->GetBool("isAttack"))
	{
		controller->ChangeState(controller->GetState("Attack"));
	}
	else if (velocityX > 0.01f || velocityY > 0.01f)
	{
		controller->ChangeState(controller->GetState("Walk"));
	}
}