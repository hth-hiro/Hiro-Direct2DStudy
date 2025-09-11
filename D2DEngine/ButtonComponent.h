#pragma once
#include "Component.h"
#include "InputComponent.h"
#include "D2DEngineWrapper.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"

class ButtonComponent :
	public Component
{
public:
	ButtonComponent() {}
	virtual ~ButtonComponent() = default;

	void CreateButton(GameObject* owner, std::shared_ptr<BitmapResource> bitmap, int startPosX, int startPosY, int width, int height);
	virtual void Update() override;
	virtual void OnEnable() override {}
	virtual void OnDestroy() override {}
	bool OnClick();
	bool OnMouseEnter();

private:
	bool isClicked;
	bool isMouseEnter;

	POINT m_pt;
	RECT m_rect;

	ID2D1Bitmap1* m_button;
};