#pragma once
#include <vector>
#include "GameObject.h"
#include "D2DEngineWrapper.h"
#include <d2d1.h>
#include "Define.h"

class GameObject;
class Scene
{
private:
	std::vector<GameObject*> tmpObj;
	std::vector<GameObject*> delObj;
	std::vector<GameObject*> m_Objects;
	D2D1::ColorF m_BGColor;

	ComPtr<ID2D1Bitmap1> g_d2dBitmapFromFile;
	ComPtr<IDXGIAdapter3> g_dxgiAdapter;
	ComPtr<IDXGIDevice3> g_dxgiDevice;

public:
	Scene() : m_BGColor(D2D1::ColorF(D2D1::ColorF::White)) {}
	virtual ~Scene()
	{
		Clear();
	}

	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		tmpObj.push_back(pObject);
		return pObject;
	}

	template<typename T>
	T* CreateObjectByName(std::wstring obj)
	{
		T* pObject = new T();
		tmpObj.push_back(pObject);
		return pObject;
	}

	void DestroyObject(GameObject* obj)
	{
		if (obj)
		{
			obj->m_IsDead = true;
		}
	}
	
	const std::vector<GameObject*>& GetAllObjects() const { return m_Objects; }

	void SetBGColor(const D2D1::ColorF& color) { m_BGColor = color; }
	void SetBGColor(EColor color) { m_BGColor = ToColorF(color); }
	D2D1::ColorF GetBGColor() { return m_BGColor; }

	void Clear();
	virtual void Enter();
	virtual void Exit() { Clear(); }
	virtual void Update();
	void Render();
};