#pragma once
#include <vector>
#include <queue>
#include <cstdint>
#include <cassert>
#include "Singleton.h"

class Object;
struct ObjectHandle
{
	uint32_t index = 0;			// ������ �ε���
	uint32_t generation = 0;	// ������� ����
};

class ObjectHandleTable : public Singleton<ObjectHandleTable>
{
	friend class Singleton<ObjectHandleTable>;

private:
	ObjectHandleTable() = default;
	~ObjectHandleTable() = default;

	std::vector<Object*> objects;		// ��ü ������ ����
	std::vector<uint32_t> generations;	// �� �ε����� ���� ���밪 ����
	std::queue<uint32_t> freeIndexes;	// �ı��� ��ü �ε��� ���� �� ť

public:
	template<typename T>
	T* GetTypePtr(const ObjectHandle& h) {
		Object* base = GetObjectPtr(h);
		return dynamic_cast<T*>(base);
	}

	Object* GetObjectPtr(const ObjectHandle& h) {
		if (h.index >= objects.size() || !objects[h.index]) return nullptr;
		if (generations[h.index] != h.generation) return nullptr;
		return objects[h.index];
	}

	ObjectHandle CreateHandle(Object* allocated)
	{
		// �ʱ� ���� ����
		uint32_t index = 0;
		if (freeIndexes.empty())
		{
			index = static_cast<uint32_t>(objects.size());
			generations.push_back(0);			// ���ο� �ε����� ���밪 0
			objects.push_back(allocated);
		}
		else
		{
			index = freeIndexes.front();
			freeIndexes.pop();
			generations[index]++;
			assert(objects[index] == nullptr);
			objects[index] = allocated;
		}
		return ObjectHandle{ index, generations[index] };
	}

	void DestroyHandle(const ObjectHandle& h)
	{
		if (IsValid(h))
		{
			objects[h.index] = nullptr;
			freeIndexes.push(h.index);
		}
	}

	bool IsValid(const ObjectHandle& h) const
	{
		return h.index < objects.size()
			&& objects[h.index] != nullptr
			&& generations[h.index] == h.generation;
	}

	Object* Get(const ObjectHandle& h)
	{
		if (IsValid(h)) return objects[h.index];
		return nullptr;
	}
};

template<typename T>
class WeakObjectPtr {
public:
	T* ptr = nullptr;
	ObjectHandle handle;

	WeakObjectPtr() = default;
	WeakObjectPtr(T* instance)
	{
		Set(instance);
	}

	bool IsValid() const {
		return ptr != nullptr && ObjectHandleTable::GetInstance().IsValid(handle);
	}

	void Set(T* instance) { ptr = instance; handle = instance->GetHandle(); }
	T* Get() const {
		return ObjectHandleTable::GetInstance().IsValid(handle) ? ptr : nullptr;
	}

	T* operator->() const {
		return ptr;
	}
	explicit operator bool() const {
		return IsValid();
	}

	void Reset()
	{
		ptr = nullptr;
		handle = ObjectHandle{};
	}
};