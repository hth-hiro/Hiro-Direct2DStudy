#pragma once
#include "GameObject.h"
#include "HealthComponent.h"

class Player : public GameObject
{
public:
	HealthComponent health;
	GameObject* Target = nullptr;	// ������ ��� ��ü�� ���� ������
	ObjectHandle hTarget;		// ��ü�� ��ȿ���� �˻�
	WeakObjectPtr<GameObject> wptrTarget;

	void SetTarget(GameObject* instance)
	{
		Target = instance;
		hTarget = instance->GetHandle();
		wptrTarget.Set(instance);
	}

	void Attack(int damage)
	{
		// Target�� nullptr�� �ƴϰ�, hTarget�� ��ȿ���� üũ
		if (Target != nullptr && ObjectHandleTable::GetInstance().IsValid(hTarget))
		{
			auto healthComp = Target->GetComponent<HealthComponent>();
			if (healthComp)
			{
				healthComp->TakeDamage(damage);
			}
		}

		// dangling pointer ����
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
		health.onChangeHealth.Add(this->GetHandle(), // �����̳ʿ��� �˻� Ű�� ����� ��(�ּ�)
			std::bind(&Player::OnChangeHealth,  // ������ Ŭ���� ����Լ�
				this,  // ������ Ŭ���� �ν��Ͻ� �ּ�			
				std::placeholders::_1,	//BroadCast ȣ�⿡�� OnChangeHealth�� �Ѱ��ִ� �ڸ�
				std::placeholders::_2));//BroadCast ȣ�⿡�� OnChangeHealth�� �Ѱ��ִ� �ڸ�
	}
};

