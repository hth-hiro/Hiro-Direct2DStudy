#pragma once
#include "ObjectHandleTable.h"

class Object
{
	ObjectHandle m_handle;
public:
	Object()
	{
		m_handle = ObjectHandleTable::GetInstance().CreateHandle(this);
	}
	virtual ~Object()
	{
		ObjectHandleTable::GetInstance().DestroyHandle(m_handle);

	}
	ObjectHandle GetHandle() { return m_handle; }
};