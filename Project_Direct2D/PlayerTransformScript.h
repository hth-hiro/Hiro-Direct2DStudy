#pragma once
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/InputComponent.h"
#include "../D2DEngine/AnimationController.h"
#include "../D2DEngine/SceneManager.h"

#include "IdleState.h"
#include "WalkState.h"
#include "AttackState.h"
#include "Throw.h"

#include <cmath>

class PlayerTransformScript : public ScriptComponent
{
public:
	void Awake() override
	{
		m_Scene = SceneManager::GetInstance().GetCurrentScene();
		playerTr = owner->GetComponent<TransformComponent>();
		m_Controller = owner->GetComponent<AnimationController>();

		if (m_Controller)
		{
			m_Controller->LoadAnimatorController("../Resource/json/Girl_AnimController.json");
			m_Controller->CreateState("Idle", new IdleState());
			m_Controller->ChangeState(m_Controller->GetState("Idle"));
			m_Controller->CreateState("Walk", new WalkState());
			m_Controller->CreateState("Attack", new AttackState());
		}
	}

	void Start() override
	{
		PosX = 0.0f;
		PosY = 0.0f;
	}

	void Update() override
	{
		if (InputSystem::GetInstance().IsKeyPressed(VK_F6))
		{
			PosX = 0.0f;
			PosY = 0.0f;
		}

		bool isAttack = m_Controller->GetBool("isAttack");
		bool isMoving = (std::abs(velocityX) > 0.0f || std::abs(velocityY) > 0.0f);

		if (isAttack) return;

		velocityX = 0;
		velocityY = 0;

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

		if (InputSystem::GetInstance().IsKeyPressed('X'))
		{
			if (isMoving)
			{
				velocityX = 0;
				velocityY = 0;
			}

			if (velocityX == 0 && velocityY == 0)
			{
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

			// ���� å ������ å ���ư���,
			// å �ִϸ��̼� ��� �� �������? �׷��� �����ߴµ�
			// �� �ȵǳ�...
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

		PosX += velocityX * moveSpeed * Time::GetInstance().GetDeltaTime();
		PosY += velocityY * moveSpeed * Time::GetInstance().GetDeltaTime();

		playerTr->SetTranslation(PosX, PosY);

		// Debug
		//std::cout << "[Debug] �÷��̾� ��ǥ : " << PosX << ", " << PosY << std::endl;

		m_Controller->SetFloat("velocityX", velocityX);
		m_Controller->SetFloat("velocityY", velocityY);
	}

private:
	TransformComponent* playerTr = nullptr;
	AnimationController* m_Controller = nullptr;
	Scene* m_Scene = nullptr;
	std::vector<GameObject*> m_BookObjects;
	float PosX = 0.0f;
	float PosY = 0.0f;

	float velocityX = 0.0f;
	float velocityY = 0.0f;
	float moveSpeed = 150.0f;
};