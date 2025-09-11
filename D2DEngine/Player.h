#pragma once
#include "GameObject.h"
#include "HealthComponent.h"

class Player : public GameObject
{
public:
	HealthComponent health;
	GameObject* Target = nullptr;	// 공격할 대상 객체에 대한 포인터
	ObjectHandle hTarget;		// 객체가 유효한지 검사
	WeakObjectPtr<GameObject> wptrTarget;

	void SetTarget(GameObject* instance)
	{
		Target = instance;
		hTarget = instance->GetHandle();
		wptrTarget.Set(instance);
	}

	void Attack(int damage)
	{
		// Target이 nullptr이 아니고, hTarget이 유효한지 체크
		if (Target != nullptr && ObjectHandleTable::GetInstance().IsValid(hTarget))
		{
			auto healthComp = Target->GetComponent<HealthComponent>();
			if (healthComp)
			{
				healthComp->TakeDamage(damage);
			}
		}

		// dangling pointer 방지
		else if (wptrTarget.IsValid())
		{
			auto targetLocked = wptrTarget.Get();
			if (targetLocked)
			{
				auto healthComp = Target->GetComponent<HealthComponent>();
				if (healthComp)
				{
					healthComp->TakeDamage(damage);
				}
			}

		}
	}
	
	void OnChangeHealth(int prev, int curr)
	{
		std::cout << "HP : " << prev << " -> " << curr << std::endl;
	}

	void Start()
	{
		health.onChangeHealth.Add(this->GetHandle(), // 컨테이너에서 검색 키로 사용할 값(주소)
			std::bind(&Player::OnChangeHealth,  // 실행할 클래스 멤버함수
				this,  // 실행할 클래스 인스턴스 주소			
				std::placeholders::_1,	//BroadCast 호출에서 OnChangeHealth에 넘겨주는 자리
				std::placeholders::_2));//BroadCast 호출에서 OnChangeHealth에 넘겨주는 자리
	}
};

