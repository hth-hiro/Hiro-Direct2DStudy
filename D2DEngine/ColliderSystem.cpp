#include "pch.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ColliderSystem.h"
#include "SceneManager.h"
#include "BoxColliderComponent.h"
#include "DynamicComponent.h"
#include "KinematicComponent.h"

void ColliderSystem::Enter()
{
	
}

void ColliderSystem::Update()
{
	auto* scene = SceneManager::GetInstance().GetCurrentScene();

	for (GameObject* obj : scene->GetAllObjects())
	{
		auto* colComp = obj->GetComponent<BoxColliderComponent>();
		auto* tr = obj->GetComponent<TransformComponent>();

		if (!colComp || !tr) continue;

		auto* dynComp = obj->GetComponent<DynamicComponent>();
		auto* kinComp = obj->GetComponent<KinematicComponent>();

		if (dynComp) dynComp->isGrounded = false;

		float nextX = tr->GetTranslation().x;
		float nextY = tr->GetTranslation().y;

		if (dynComp)
		{
			nextX = dynComp->nextPositionX;
			nextY = dynComp->nextPositionY;
		}
		else if (kinComp)
		{
			nextX = kinComp->nextPositionX;
			nextY = kinComp->nextPositionY;
		}
		else
		{
			continue;
		}

		AABB newAABB(nextX, nextY, colComp->GetAABB().halfW, colComp->GetAABB().halfH);
		
		for (GameObject* other : scene->GetAllObjects())
		{
			if (other == obj) continue;

			auto* otherCol = other->GetComponent<BoxColliderComponent>();
			if (!otherCol) continue;

			const AABB& otherAABB = otherCol->GetAABB();

			if (newAABB.Blocks(otherAABB))
			{
				Direction dir = newAABB.GetCollisionDirection(otherAABB);

				if (colComp->isTrigger || otherCol->isTrigger)
				{
					colComp->OnTriggerEnter(other);
					otherCol->OnTriggerEnter(obj);
				}
				else
				{
					colComp->OnCollisionEnter(other);
					otherCol->OnCollisionEnter(obj);
				}

				//if (newAABB.Overlaps(otherAABB))
				//{
				//	float dx = otherAABB.centerX - newAABB.centerX;
				//	float dy = otherAABB.centerY - newAABB.centerY;

				//	float overlapX = (newAABB.halfW + otherAABB.halfW) - std::abs(dx);
				//	float overlapY = (newAABB.halfH + otherAABB.halfH) - std::abs(dy);

				//	if (overlapX < overlapY)
				//	{
				//		// X 방향 밀림 처리
				//		if (dx > 0)
				//		{
				//			// aabb1가 왼쪽에 있으므로 왼쪽으로 밀림
				//			newAABB.centerX -= overlapX + 5;
				//		}
				//		else
				//		{
				//			newAABB.centerX += overlapX + 5;
				//		}
				//	}
				//	else
				//	{
				//		// Y 방향 밀림 처리
				//		if (dy > 0)
				//		{
				//			newAABB.centerY -= overlapY;
				//		}
				//		else
				//		{
				//			newAABB.centerY += overlapY;
				//		}
				//	}
				//}

				switch (dir)
				{
				case Direction::Bottom:
				{
					if (dynComp && dynComp->GetVelocityY() < 0.0f)
					{
						dynComp->isGrounded = true;
						dynComp->SetVelocity(dynComp->GetVelocityX(), 0);
						nextY = tr->GetTranslation().y;
					}

					else if (kinComp && kinComp->GetVelocityY() < 0.0f)
					{
						kinComp->SetVelocity(kinComp->GetVelocityX(), 0);
						nextY = tr->GetTranslation().y;
					}
					break;
				}
				case Direction::Top:
				{
					if (dynComp && dynComp->GetVelocityY() > 0.0f)
					{
						dynComp->SetVelocity(dynComp->GetVelocityX(), 0);
						nextY = tr->GetTranslation().y;
					}

					else if (kinComp && kinComp->GetVelocityY() > 0.0f)
					{
						kinComp->SetVelocity(kinComp->GetVelocityX(), 0);
						nextY = tr->GetTranslation().y;
					}
					break;
				}
				case Direction::Left:
				{
					if (dynComp && dynComp->GetVelocityX() < 0.0f)
					{
						nextX = tr->GetTranslation().x;
						dynComp->SetVelocity(0, dynComp->GetVelocityY());
					}

					else if (kinComp && kinComp->GetVelocityX() < 0.0f)
					{
						kinComp->SetVelocity(0, kinComp->GetVelocityY());
						nextX = tr->GetTranslation().x;
					}
					break;
				}
				case Direction::Right:
				{
					if (dynComp && dynComp->GetVelocityX() > 0.0f)
					{
						nextX = tr->GetTranslation().x;
						dynComp->SetVelocity(0, dynComp->GetVelocityY());
					}

					else if (kinComp && kinComp->GetVelocityX() > 0.0f)
					{
						kinComp->SetVelocity(0, kinComp->GetVelocityY());
						nextX = tr->GetTranslation().x;
					}
				}
					break;
				}
			}
		}

		if (dynComp)
		{
			dynComp->nextPositionX = nextX;
			dynComp->nextPositionY = nextY;
		}

		else if (kinComp)
		{
			kinComp->nextPositionX = nextX;
			kinComp->nextPositionY = nextY;
		}
	}

	for (auto* obj : scene->GetAllObjects())
	{
		auto* dynComp = obj->GetComponent<DynamicComponent>();
		auto* kinComp = obj->GetComponent<KinematicComponent>();
		auto* tr = obj->GetComponent<TransformComponent>();

		if (!tr) continue;

		if (dynComp)
		{
			tr->SetTranslation(dynComp->nextPositionX, dynComp->nextPositionY);
		}
		else if (kinComp)
		{
			tr->SetTranslation(kinComp->nextPositionX, kinComp->nextPositionY);
		}
	}
}
