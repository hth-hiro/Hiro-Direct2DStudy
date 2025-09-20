#pragma once
#include "UIComponent.h"
#include "InputComponent.h"
#include "D2DEngineWrapper.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"

// 버튼의 상태를 관리합니다. (기존 버튼 렌더는 삭제 예정)

class NewButtonComponent : public UIComponent
{
public:
	NewButtonComponent() {}
	virtual ~NewButtonComponent() = default;

	void Create(GameObject* owner, std::shared_ptr<BitmapResource> bitmap, RECT rect);

	virtual void Update() override;
	virtual void OnEnable() override {}
	virtual void OnDestroy() override {}

	// 클릭 이벤트 처리
	bool OnClick();
	bool OnMouseEnter();

	void Render() override; // 렌더

private:
	bool isClicked;
	bool isMouseEnter;

	POINT m_pt;
	RECT m_rect;

	ID2D1Bitmap1* m_button;
};

