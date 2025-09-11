#include "Throw.h"
#include "BookAnimScript.h"

void Throw::Enter(AnimationController* controller)
{
	auto* animator = controller->GetAnimator();
	if (animator)
		animator->SetAnimationClip(&BookAnimScript::thrownClip);
}

void Throw::Update(AnimationController* controller)
{

}
