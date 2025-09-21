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
			// ScriptComponent �ǳʶٱ�
			if (dynamic_cast<ScriptComponent*>(comp)) continue;

			comp->Awake();
		}
	}

	void Start()
	{
		for (Component* comp : m_Components)
		{
			// ScriptComponent �ǳʶٱ�
			if (dynamic_cast<ScriptComponent*>(comp)) continue;

			comp->Start();
		}
	}

	void Update()
	{
		for (Component* comp : m_Components)
		{
			// ScriptComponent �ǳʶٱ�
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

		// TransformComponent Ư�� ó��
		if constexpr (std::is_same_v<T, TransformComponent>)
		{
			m_TransformComponent = comp;
		}

		comp->Awake();
		comp->OnEnable();
		return comp;
	}

	// ���� ���� ������Ʈ�� ��ȯ�Ѵ�.
	// Ÿ�� T�� ��ӵǾ��ų� TŸ�԰� ��ġ�ϴ� ��� Component�� ã��
	// �ش� Ÿ���� ��� ������Ʈ���� ����Ʈ�� ��ȯ�Ѵ�.
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

	// �ϳ��� ������Ʈ�� ��ȯ�Ѵ�.
	// Ÿ���� ��Ȯ�� T�� ��ġ�ϴ� ������Ʈ�� ã��
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

