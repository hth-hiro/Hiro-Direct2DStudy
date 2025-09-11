#include "AttackState.h"
#include "AnimeRenderScript.h"

void AttackState::Enter(AnimationController* controller)
{
	auto* animator = controller->GetAnimator();
	if (animator)
		animator->SetAnimationClip(&AnimeRenderScript::attackClip);
}

void AttackState::Update(AnimationController* controller)
{
	float velocityX = std::abs(controller->GetFloat("velocityX"));
	float velocityY = std::abs(controller->GetFloat("velocityY"));

	auto* animator = controller->GetAnimator();
	if (!animator) return;

	if (animator->IsAnimationDone())
	{
		controller->SetBool("isAttack", false);
		controller->ChangeState(controller->GetState("Idle"));
	}
	else if (velocityX > 0.01f || velocityY > 0.01f)
	{
		controller->ChangeState(controller->GetState("Walk"));
	}
}