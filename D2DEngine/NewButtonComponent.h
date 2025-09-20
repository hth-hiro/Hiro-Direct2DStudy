#pragma once
#include "UIComponent.h"
#include "InputComponent.h"
#include "D2DEngineWrapper.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"

// ��ư�� ���¸� �����մϴ�. (���� ��ư ������ ���� ����)

class NewButtonComponent : public UIComponent
{
public:
	NewButtonComponent() {}
	virtual ~NewButtonComponent() = default;

	void Create(GameObject* owner, std::shared_ptr<BitmapResource> bitmap, RECT rect);

	virtual void Update() override;
	virtual void OnEnable() override {}
	virtual void OnDestroy() override {}

	// Ŭ�� �̺�Ʈ ó��
	bool OnClick();
	bool OnMouseEnter();

	void Render() override; // ����

private:
	bool isClicked;
	bool isMouseEnter;

	POINT m_pt;
	RECT m_rect;

	ID2D1Bitmap1* m_button;
};

