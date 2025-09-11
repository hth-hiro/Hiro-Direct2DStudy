#include "pch.h"
#include "InputSystem.h"
#include "InputComponent.h"

InputSystem::InputSystem()
{
	memset(m_PrevState, 0, sizeof(m_PrevState));
	memset(m_CurrState, 0, sizeof(m_CurrState));
}

InputSystem::~InputSystem()
{
	m_Components.clear();
}

void InputSystem::Startup(HWND hWnd)
{
	m_hWnd = hWnd;

	// 키보드 상태 초기화
	for (int i = 0; i < 256; i++)
	{
		m_CurrState[i] = GetAsyncKeyState(i);
		m_PrevState[i] = m_CurrState[i];
	}

	// 마우스 좌표 초기화
	::GetCursorPos(&m_mouseClient);
	::ScreenToClient(m_hWnd, &m_mouseClient);
}

void InputSystem::Update()
{
	::GetCursorPos(&m_mouseClient);
	::ScreenToClient(m_hWnd, &m_mouseClient);

	m_mouseWheelDelta = 0;

	memcpy_s(m_PrevState, sizeof(m_PrevState), m_CurrState, sizeof(m_CurrState));
	for (int i = 0; i < 256; i++)
	{
		m_CurrState[i] = GetAsyncKeyState(i);
	}

 	for (InputComponent* comp : m_Components)
	{
		if (comp)
		{
			comp->Update();
		}
	}
}

// 키가 눌려있는가
bool InputSystem::IsKeyDown(int vKey)
{
	return (m_CurrState[vKey] & 0x8000) != 0;
}

// 이번 프레임에 처음 눌렀는가
bool InputSystem::IsKeyPressed(int vKey)
{
	return (!(m_PrevState[vKey] & 0x8000) && (m_CurrState[vKey] & 0x8000));
}

bool InputSystem::IsKeyReleased(int vKey)
{
	return ((m_PrevState[vKey] & 0x8000) && !(m_CurrState[vKey] & 0x8000));
}

bool InputSystem::IsAnyKeyPressed()
{
	for (int i = 0; i < 256; ++i)
	{
		if (!(m_PrevState[i] & 0x8000) && (m_CurrState[i] & 0x8000))
			return true;
	}
	return false;
}

POINT InputSystem::GetMousePosition() const
{
	return m_mouseClient;
}

void InputSystem::SetMousePosition(HWND hWnd, int mousePosX, int mousePosY)
{
	m_hWnd = hWnd;

	POINT pt = { mousePosX, mousePosY };
	ClientToScreen(m_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
}

void InputSystem::Register(InputComponent* comp)
{
	if (comp)
	{
		auto it = std::find(m_Components.begin(), m_Components.end(), comp);
		if (it == m_Components.end()) {
			m_Components.push_back(comp);
		}
	}
}

void InputSystem::Unregister(InputComponent* comp)
{
	if (comp)
	{
		m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());
	}
}