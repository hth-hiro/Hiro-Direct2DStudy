#pragma once
#include <functional>
#include "ObjectHandleTable.h"

template<typename... Args>
class MultiDelegate
{
	struct Slot
	{
		ObjectHandle handle;
		std::function<void(Args...)> func;
	};
	std::vector<Slot> slots;

public:
	void Add(ObjectHandle handle, const std::function<void(Args...)>& f)
	{
		slots.push_back({ handle, f });
	}

	void Remove(ObjectHandle handle)
	{
		slots.erase(
			std::remove_if(slots.begin(), slots.end(),
				[handle](const Slot& s) {return s.handle == handle; }),
			slots.end());
	}

	void Clear() { slots.clear(); }

	void BroadCast(Args... args) const
	{
		for (const auto& s : slots)
		{
			if (ObjectHandleTable::GetInstance().IsValid(s.handle))
				s.func(args...);
		}
	}
};