#include "pch.h"
#include "Camera.h"
#include "InputComponent.h"
#include "Time.h"

void Camera::Reset()
{
	m_CameraSpeed = 1.0f;
	m_MoveSpeed = 150.0f;
	m_wheelDelta = 0;
	m_IsFPS = false;
	m_ScaleRange = 0.1f;
	m_CameraTransform.Reset();
	m_prevMousePos = InputSystem::GetInstance().GetMousePosition();

	//D2DEngineWrapper::GetInstance().matCameraInv = Camera::GetInstance().m_CameraTransform.ToMatrix();
	//D2DEngineWrapper::GetInstance().matCameraInv.Invert();
}

void Camera::Update()
{
	if (InputSystem::GetInstance().IsKeyPressed(VK_F6))
	{
		if (m_IsFPS)
		{
			Reset();
			return;
		}

		if (!m_IsFPS)
		{
			m_IsFPS = true;
			m_ScaleRange = 0.2f;

			m_CameraSpeed = 1.0f;
			m_MoveSpeed = 150.0f;
			m_wheelDelta = 0;

			m_CameraTransform.Reset();

			return;
		}
	}

	/////
	if (m_IsFPS)
	{
		SetCursor(LoadCursorW(nullptr, IDC_ICON));
		InputSystem::GetInstance().SetMousePosition(m_hWnd, m_Width / 2.0f, m_Height / 2.0f);

		if (InputSystem::GetInstance().IsKeyDown('W'))
		{
			m_CameraTransform.AddScale(-m_ScaleRange * Time::GetInstance().GetDeltaTime(), -m_ScaleRange * Time::GetInstance().GetDeltaTime());

			m_CameraSpeed = std::max<float>(0.01f, m_CameraSpeed - m_ScaleRange);

			if (m_CameraTransform.GetScale().width < 0 || m_CameraTransform.GetScale().height < 0)
			{
				m_CameraTransform.SetScale(0.01f, 0.01f);
			}
		}

		if (InputSystem::GetInstance().IsKeyDown('S'))
		{
			m_CameraTransform.AddScale(m_ScaleRange * Time::GetInstance().GetDeltaTime(), m_ScaleRange * Time::GetInstance().GetDeltaTime());

			m_CameraSpeed += m_ScaleRange;
		}

		if (InputSystem::GetInstance().IsKeyPressed(VK_LCONTROL))
		{
			m_CameraTransform.translation.y -= 9000 * Time::GetInstance().GetDeltaTime();

			if (m_CameraTransform.translation.y <= -200) m_CameraTransform.translation.y = -200;
		}

		if (InputSystem::GetInstance().IsKeyReleased(VK_LCONTROL))
		{
			while (m_CameraTransform.translation.y <= 0)
			{
				m_CameraTransform.translation.y += 0.001f *  Time::GetInstance().GetDeltaTime();
			}
		}
	}
	else    // FPS X
	{
		if (InputSystem::GetInstance().IsKeyDown('W'))
		{
			m_CameraTransform.translation.y += m_MoveSpeed * Time::GetInstance().GetDeltaTime();
		}

		if (InputSystem::GetInstance().IsKeyDown('S'))
		{
			m_CameraTransform.translation.y -= m_MoveSpeed * Time::GetInstance().GetDeltaTime();
		}

		if (InputSystem::GetInstance().IsKeyDown(VK_LCONTROL))
		{
			SetCursor(LoadCursorW(nullptr, IDC_CROSS));

			if (m_wheelDelta > 0)
			{
				m_CameraTransform.AddScale(-m_ScaleRange, -m_ScaleRange);

				m_CameraSpeed = std::max<float>(0.01f, m_CameraSpeed - m_ScaleRange);

				if (m_CameraTransform.GetScale().width < 0 || m_CameraTransform.GetScale().height < 0)
				{
					m_CameraTransform.SetScale(0.01f, 0.01f);
				}
			}
			else if (m_wheelDelta < 0)
			{
				m_CameraTransform.AddScale(m_ScaleRange, m_ScaleRange);

				m_CameraSpeed += m_ScaleRange;
			}
		}
		else if (InputSystem::GetInstance().IsKeyReleased(VK_LCONTROL))
		{
			SetCursor(LoadCursorW(nullptr, IDC_ARROW));
		}

		m_wheelDelta = InputSystem::GetInstance().GetMouseWheelDelta();

		if (InputSystem::GetInstance().IsKeyDown(VK_MBUTTON))
		{
			SetCursor(LoadCursorW(nullptr, IDC_SIZEALL));

			POINT currentpt = InputSystem::GetInstance().GetMousePosition();

			int dx = m_prevMousePos.x - currentpt.x;
			int dy = m_prevMousePos.y - currentpt.y;

			m_CameraTransform.translation.x += dx * m_CameraSpeed;
			m_CameraTransform.translation.y -= dy * m_CameraSpeed;
		}
		else if (InputSystem::GetInstance().IsKeyReleased(VK_MBUTTON))
		{
			SetCursor(LoadCursorW(nullptr, IDC_ARROW));
		}
		m_prevMousePos = InputSystem::GetInstance().GetMousePosition();
	}

	//////

	if (InputSystem::GetInstance().IsKeyPressed(VK_LSHIFT))
	{
		m_MoveSpeed = 450.0f;
		m_ScaleRange = 0.6f;
	}
	else if (InputSystem::GetInstance().IsKeyReleased(VK_LSHIFT))
	{
		m_MoveSpeed = 150.0f;
		m_ScaleRange = 0.2f;
	}

	/////

	if (InputSystem::GetInstance().IsKeyDown('A'))
	{
		m_CameraTransform.translation.x -= m_MoveSpeed * Time::GetInstance().GetDeltaTime();
	}

	if (InputSystem::GetInstance().IsKeyDown('D'))
	{
		m_CameraTransform.translation.x +=  m_MoveSpeed * Time::GetInstance().GetDeltaTime();
	}

	if (InputSystem::GetInstance().IsKeyPressed('R'))
	{
		Reset();
	}
}