#pragma once
#include <vector>
#include <windows.h>
#include "Singleton.h"

class InputComponent;
class InputSystem : public Singleton<InputSystem>
{
private:
	HWND m_hWnd;
	POINT m_mouseClient;
	SHORT m_PrevState[256] = { 0, };
	SHORT m_CurrState[256] = { 0, };
	short m_mouseWheelDelta;

public:
    InputSystem();
    virtual ~InputSystem();
	std::vector<InputComponent*> m_Components;

	void Startup(HWND hWnd);
	void Shutdown() {};
	void Update();

	bool IsKeyDown(int vKey);
	bool IsKeyPressed(int vKey);
	bool IsKeyReleased(int vKey);
	bool IsAnyKeyPressed();

	POINT GetMousePosition() const;
	void SetMousePosition(HWND hWnd, int mousePosX, int mousePosY);
	void SetMouseWheelDelta(short delta) { m_mouseWheelDelta = delta; }
	short GetMouseWheelDelta() const { return m_mouseWheelDelta; }

	void Register(InputComponent* comp);
	void Unregister(InputComponent* comp);

private:
	float m_sleepTick = 0.0f;
};