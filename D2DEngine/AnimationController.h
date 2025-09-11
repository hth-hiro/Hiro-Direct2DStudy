#pragma once
#include "pch.h"
#include "Component.h"
#include <unordered_map>
#include "AnimatorComponent.h"

class AnimationBaseState;
class AnimationController : public Component
{
public:
	void LoadAnimatorController(const std::string& filePath);

	void Awake() override;
	void Update() override;
	void SetNextContainer();

	void CreateState(const std::string& name, AnimationBaseState* state);
	void ChangeState(AnimationBaseState* newState);

	// Setter
	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);

	// Getter
	bool GetBool(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	AnimatorComponent* GetAnimator() { return m_animator; }
	AnimationBaseState* GetState(const std::string& stateName);

	void OnEnable() override {}
	void OnDestroy() override {}

private:
	std::unordered_map<std::string, bool> m_boolParams;
	std::unordered_map<std::string, float> m_floatParams;
	std::unordered_map<std::string, AnimationBaseState*> m_StateContainer;

	AnimatorComponent* m_animator = nullptr;

	AnimationBaseState* m_pCurrState = nullptr;
	AnimationBaseState* m_pNextState = nullptr;
};

