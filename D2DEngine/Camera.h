#pragma once
#include "TransformComponent.h"
#include "Singleton.h"
#include "D2DEngineWrapper.h"

class Camera : public Singleton<Camera>
{
public:
	Camera() { Reset(); }
	TransformComponent m_CameraTransform;

	void Reset();
	void Update();

private:
	float m_CameraSpeed = 1.0f;
	float m_MoveSpeed = 150.0f;
	float m_ScaleRange = 0.1f;
	short m_wheelDelta = 0;
	bool m_IsFPS = false;

	float m_prevSmoothX = 0.0f;
	float m_prevSmoothY = 0.0f;
	float smoothingFactor = 0.2f;

	POINT m_prevMousePos;
	HWND m_hWnd = D2DEngineWrapper::GetInstance().m_hwnd;
	int m_Width = D2DEngineWrapper::GetInstance().m_ClientWidth;
	int m_Height = D2DEngineWrapper::GetInstance().m_ClientHeight;
};