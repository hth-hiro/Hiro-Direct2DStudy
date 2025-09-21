#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include "ScriptComponent.h"
#include "TransformComponent.h"

class Component;
class GameObject : public Object
{
	friend class Scene;

private:
	std::vector<Component*> m_Components;
	TransformComponent* m_TransformComponent = nullptr;
	bool m_isUI = false;
	std::string m_Name;
	Scene* m_Scene = nullptr;

public:
	GameObject()
	{
		AddComponent<TransformComponent>();
	}
	~GameObject()
	{
		for (Component* comp : m_Components)
		{
			comp->OnDestroy();
			delete comp;
		}
		m_Components.clear();
	}

	void Awake()
	{
		for (Component* comp : m_Components)
		{
			// ScriptComponent 건너뛰기
			if (dynamic_cast<ScriptComponent*>(comp)) continue;

			comp->Awake();
		}
	}

	void Start()
	{
		for (Component* comp : m_Components)
		{
			// ScriptComponent 건너뛰기
			if (dynamic_cast<ScriptComponent*>(comp)) continue;

			comp->Start();
		}
	}

	void Update()
	{
		for (Component* comp : m_Components)
		{
			// ScriptComponent 건너뛰기
			if (dynamic_cast<ScriptComponent*>(comp)) continue;

			comp->Update();
		}
	}

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_base_of < Component, T>::value, "T must derive from Component");

		T* comp = new T(std::forward<Args>(args)...);

		comp->owner = this;
		m_Components.push_back(comp);

		// TransformComponent 특별 처리
		if constexpr (std::is_same_v<T, TransformComponent>)
		{
			m_TransformComponent = comp;
		}

		comp->Awake();
		comp->OnEnable();
		return comp;
	}

	// 여러 개의 컴포넌트를 반환한다.
	// 타입 T로 상속되었거나 T타입과 일치하는 모든 Component를 찾음
	// 해당 타입의 모든 컴포넌트들은 리스트로 반환한다.
	template<typename T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> result;
		for (Component* comp : m_Components)
		{
			if (auto casted = dynamic_cast<T*>(comp))
			{
				result.push_back(casted);
			}
		}
		return result;
	}

	// 하나의 컴포넌트만 반환한다.
	// 타입이 정확히 T와 일치하는 컴포넌트를 찾음
	template<typename T>
	T* GetComponent()
	{
		for (Component* comp : m_Components)
		{
			if (typeid(*comp) == typeid(T))
			{
				return static_cast<T*>(comp);
			}
		}
		return nullptr;
	}

	template<typename T>
	bool RemoveComponent(T* target)
	{
		for (auto it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			if (*it == target)
			{
				(*it)->OnDestroy();
				delete* it;
				m_Components.erase(it);
				return true;
			}
		}
		return false;
	}

	virtual void Render() {}

	void SetUI(bool value) { m_isUI = value; }
	bool isUI() const { return m_isUI; }

	void SetScene(Scene* scene) { m_Scene = scene; }
	Scene* GetScene() const { return m_Scene; }

	const std::string& GetName() const { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }

	bool m_IsDead = false;

	TransformComponent* GetTransform() const { return m_TransformComponent; }
};

