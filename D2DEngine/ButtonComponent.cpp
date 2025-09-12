#include "pch.h"
#include "ButtonComponent.h"
#include "BitmapResource.h"

void ButtonComponent::CreateButton(GameObject* owner, std::shared_ptr<BitmapResource> bitmap, int startPosX, int startPosY, int width, int height)
{
	m_button = bitmap->GetBitmap();

	owner->SetUI(true);
	TransformComponent* buttonTransform = owner->AddComponent<TransformComponent>();
	buttonTransform->SetTranslation(
		startPosX + width * 0.5f - D2DEngineWrapper::GetInstance().m_ClientWidth / 2,
		-startPosY - height * 0.5f + D2DEngineWrapper::GetInstance().m_ClientHeight / 2);
	buttonTransform->SetScale(width / m_button->GetSize().width, height / m_button->GetSize().height);
	SpriteRenderComponent* buttonSprite = owner->AddComponent<SpriteRenderComponent>();
	buttonSprite->SetBitmap(bitmap);
	m_rect = { startPosX, startPosY, width + startPosX, height + startPosY };
}

void ButtonComponent::Update()
{
	m_pt = InputSystem::GetInstance().GetMousePosition();
	if (PtInRect(&m_rect, m_pt))
	{
		OnMouseEnter();

		isMouseEnter = true;
		SetCursor(LoadCursorW(nullptr, IDC_HAND));
		if (InputSystem::GetInstance().IsKeyPressed(VK_LBUTTON))
		{
			isClicked = true;
		}
	}
	else
	{
		isMouseEnter = false;
	}

	//isClicked = false;
}

bool ButtonComponent::OnClick()
{
	if (isClicked)
	{
		isClicked = false;
		return true;
	}

	return false;
}

bool ButtonComponent::OnMouseEnter()
{
	return false;
}

// Mouse State
// IDC_APPSTARTING		Arrow + Loading
// IDC_CROSS 			Cross
// IDC_HAND 			toClick
// IDC_HELP 			Arrow + ?
// IDC_IBEAM 			Text Input
// IDC_ICON				Invisibility
// IDC_NO 				Ban
// IDC_PERSON			Arrow + Person Mark
// IDC_PIN				Arrow + Pin Mark
// IDC_SIZEALL			SizeControl All
// IDC_SIZENESW			 
// IDC_SIZENS			
// IDC_SIZENWSE			
// IDC_SIZEWE			
// IDC_UPARROW
// IDC_WAIT				Loading