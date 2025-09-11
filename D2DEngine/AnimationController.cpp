#include "pch.h"
#include <fstream>
#include "json.hpp"
#include "AnimationController.h"
#include "AnimatorComponent.h"
#include "AnimationBaseState.h"

void AnimationController::LoadAnimatorController(const std::string& filePath)
{
	std::ifstream inFile(filePath);
	if (inFile.is_open())
	{
		json j;
		inFile >> j;
		inFile.close();

		for (const auto& param : j["paremeters"])
		{
			std::string name = param["name"];	// 파라미터의 이름
			std::string type = param["type"];	// 파라미터의 자료형

			if (type == "Bool")
			{
				m_boolParams[name] = param["defaultBool"];
			}
			else if (type == "Float")
			{
				m_floatParams[name] = param["defaultFloat"];
			}
		}
	}
	else {
		throw std::runtime_error("Error");
	}
}

void AnimationController::Awake()
{
	m_animator = owner->GetComponent<AnimatorComponent>();
}

void AnimationController::Update()
{
	if (m_pCurrState)
		m_pCurrState->Update(this);

	if (m_pNextState && m_pNextState != m_pCurrState)
	{
		ChangeState(m_pNextState);
		m_pNextState = nullptr;
	}
}

void AnimationController::SetNextContainer()
{
	
}

void AnimationController::CreateState(const std::string& name, AnimationBaseState* state)
{
	m_StateContainer[name] = state;
}

void AnimationController::SetBool(const std::string& name, bool value)
{
	m_boolParams[name] = value;
}

void AnimationController::SetFloat(const std::string& name, float value)
{
	m_floatParams[name] = value;
}

bool AnimationController::GetBool(const std::string& name) const
{
	auto it = m_boolParams.find(name);
	return (it != m_boolParams.end()) ? it->second : false;
}

float AnimationController::GetFloat(const std::string& name) const
{
	auto it = m_floatParams.find(name);
	return (it != m_floatParams.end()) ? it->second : 0.0f;
}

AnimationBaseState* AnimationController::GetState(const std::string& state)
{
	auto it = m_StateContainer.find(state);
	if (it != m_StateContainer.end())
		return it->second;

	return nullptr;
}

void AnimationController::ChangeState(AnimationBaseState* newState)
{
	//if (m_pCurrState == newState) return;

	if (m_pCurrState)
		m_pCurrState->Exit(this);

	m_pCurrState = newState;

	if (m_pCurrState)
		m_pCurrState->Enter(this);
}