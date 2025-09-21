#include "pch.h"
#include "NewButtonComponent.h"

void NewButtonComponent::Create(GameObject* owner, std::unordered_map<EButtonState, std::shared_ptr<BitmapResource>>& bitmaps, RECT rect)
{
	this->owner = owner;
	m_rect = rect;


	// 기존 버튼 컴포넌트 그대로 갖고옴. 수정 필요
	TransformComponent* buttonTransform = owner->AddComponent<TransformComponent>();
	float width = static_cast<float>(rect.right - rect.left);
	float height = static_cast<float>(rect.bottom - rect.top);

	buttonTransform->SetTranslation(
		rect.left + width * 0.5f - D2DEngineWrapper::GetInstance().m_ClientWidth / 2.0f,
		-rect.top - height * 0.5f + D2DEngineWrapper::GetInstance().m_ClientHeight / 2.0f);
	
	auto firstBitmap = bitmaps.begin()->second;
	buttonTransform->SetScale(width / firstBitmap.get()->GetBitmap()->GetSize().width, height / firstBitmap.get()->GetBitmap()->GetSize().height);
	
	SpriteRenderComponent* buttonSprite = owner->AddComponent<SpriteRenderComponent>();
	buttonSprite->SetBitmap(firstBitmap);

	for (auto& pair : bitmaps)
	{
		m_bitmaps[pair.first] = pair.second->GetBitmap();
	}

    m_State = EButtonState::Normal;
}

void NewButtonComponent::Update()
{
	POINT mousePos = InputSystem::GetInstance().GetMousePosition();
	bool isOver = HitTest(mousePos);

	if (isOver && m_State != EButtonState::Pressed && m_State != EButtonState::Disabled)
	{
		if (m_State != EButtonState::Hovered)
			HandleMouseEnter();
	}
	else if (!isOver && m_State != EButtonState::Disabled)
	{
		if (m_State != EButtonState::Normal)
			HandleMouseExit();
	}

	if (isOver && InputSystem::GetInstance().IsKeyDown(VK_LBUTTON))		HandleMouseDown();
	if (InputSystem::GetInstance().IsKeyReleased(VK_LBUTTON))			HandleMouseUp();
}

void NewButtonComponent::Render()
{
	ID2D1Bitmap1* bitmap = m_bitmaps[m_State];
	if (!bitmap) return;
}

void NewButtonComponent::SetState(EButtonState state)
{
	m_State = state;
}

bool NewButtonComponent::HitTest(POINT pt) const
{
	return (PtInRect(&m_rect, pt));
}

void NewButtonComponent::HandleMouseEnter()
{
	SetState(EButtonState::Hovered);
	if (onHover) onHover();
}

void NewButtonComponent::HandleMouseExit()
{
	SetState(EButtonState::Normal);
}

void NewButtonComponent::HandleMouseDown()
{
	SetState(EButtonState::Pressed);
	if (onPress) onPress();
}

void NewButtonComponent::HandleMouseUp()
{
	if (m_State == EButtonState::Pressed)
	{
		if (HitTest(InputSystem::GetInstance().GetMousePosition()) && onClick)
			onClick();

		SetState(HitTest(InputSystem::GetInstance().GetMousePosition()) ? EButtonState::Hovered : EButtonState::Normal);
	}
}
