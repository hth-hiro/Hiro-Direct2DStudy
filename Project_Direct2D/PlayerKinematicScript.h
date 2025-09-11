#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/SceneManager.h"
#include "../D2DEngine/BoxColliderComponent.h"
#include "../D2DEngine/KinematicComponent.h"

#include "IdleState.h"
#include "WalkState.h"
#include "AttackState.h"
#include "Throw.h"

#include <cmath>

class PlayerKinematicScript : public ScriptComponent
{
public:
	void Awake() override
	{
		m_Scene = SceneManager::GetInstance().GetCurrentScene();
		m_Controller = owner->GetComponent<AnimationController>();
		m_PlayerCol = owner->GetComponent<BoxColliderComponent>();
		m_kinematic = owner->GetComponent<KinematicComponent>();

		if (m_Controller)
		{
			m_Controller->LoadAnimatorController("../Resource/json/Girl_AnimController.json");
			m_Controller->CreateState("Idle", new IdleState());
			m_Controller->ChangeState(m_Controller->GetState("Idle"));
			m_Controller->CreateState("Walk", new WalkState());
			m_Controller->CreateState("Attack", new AttackState());
		}

		playerTr = owner->GetComponent<TransformComponent>();
	}

	void Start() override
	{

	}

	void Update() override
	{
		velocityX = 0.0f;
		velocityY = 0.0f;

		if (InputSystem::GetInstance().IsKeyPressed(VK_F6))
		{
			m_kinematic->SetVelocity(0, 0);
			playerTr->SetTranslation(0, 0);
			playerTr->SetScale(2.0f, 2);
		}

		bool isAttack = m_Controller->GetBool("isAttack");
		if (isAttack) return;

		m_PlayerCol->SetSize(20, 74, 0, 0);

		if (InputSystem::GetInstance().IsKeyDown(VK_LEFT))
		{
			velocityX -= 1.0f;
			playerTr->SetScale(-2.0f, 2);	// flip
			//playerTr->SetTranslation()
		}

		if (InputSystem::GetInstance().IsKeyDown(VK_RIGHT))
		{
			velocityX += 1.0f;
			playerTr->SetScale(2.0f, 2);
		}

		if (InputSystem::GetInstance().IsKeyDown(VK_UP))
		{
			velocityY += 1.0f;
		}

		if (InputSystem::GetInstance().IsKeyDown(VK_DOWN))
		{
			velocityY -= 1.0f;
		}

		float normalize = std::sqrt(velocityX * velocityX + velocityY * velocityY);

		if (normalize > 0.0f)
		{
			velocityX /= normalize;
			velocityY /= normalize;
		}

		m_kinematic->SetVelocity(velocityX * moveSpeed, velocityY * moveSpeed);
		bool isMoving = (std::abs(velocityX) > 0.0f || std::abs(velocityY) > 0.0f);

		if (InputSystem::GetInstance().IsKeyPressed('X'))
		{
			if (isMoving)
			{
				velocityX = 0;
				velocityY = 0;
				m_kinematic->SetVelocity(0, 0);
			}

			if (velocityX == 0 && velocityY == 0)
			{
				m_PlayerCol->SetSize(20, 74, -8, 0);
				m_Controller->SetBool("isAttack", true);
			}

			//GameObject* book = m_Scene->CreateObject<ThrownBook>();
			//m_BookObjects.push_back(book);

			//auto* tr = book->AddComponent<TransformComponent>();
			//tr->SetScale(2, 2);
			//tr->SetTranslation(0,0);

			//auto* bookAni = book->AddComponent<AnimationController>();
			//if (!bookAni) return;

			//bookAni->LoadAnimatorController("../Resource/json/Book_Throw_AnimController.json");
			//bookAni->CreateState("Throw", new Throw());
			//bookAni->ChangeState(bookAni->GetState("Throw"));

			//m_Controller->SetBool("isThrow", true);

			// 뭔가 책 던지고서 책 날아가고,
			// 책 애니메이션 재생 후 사라지는? 그런거 생각했는데
			// 잘 안되네...
		}

		//if (InputSystem::Instance().IsKeyPressed('L'))
		//{
		//	if (!m_BookObjects.empty())
		//	{
		//		GameObject* book = m_BookObjects.back();
		//		m_Scene->DestroyObject(book);
		//		m_BookObjects.pop_back();
		//	}
		//}

		// Debug
		//std::cout << "[Debug] 플레이어 좌표 : " << PosX << ", " << PosY << std::endl;

		m_Controller->SetFloat("velocityX", velocityX);
		m_Controller->SetFloat("velocityY", velocityY);
	}

private:
	TransformComponent* playerTr = nullptr;
	KinematicComponent* m_kinematic = nullptr;
	AnimationController* m_Controller = nullptr;
	BoxColliderComponent* m_PlayerCol = nullptr;
	Scene* m_Scene = nullptr;
	std::vector<GameObject*> m_BookObjects;
	float PosX = 0.0f;
	float PosY = 0.0f;

	float velocityX = 0.0f;
	float velocityY = 0.0f;
	float moveSpeed = 150.0f;
};