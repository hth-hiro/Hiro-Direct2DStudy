#pragma once
#include "UIComponent.h"
#include "InputComponent.h"
#include "D2DEngineWrapper.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"
#include <unordered_map>
#include <algorithm>
#include <functional>

// 버튼의 상태를 관리합니다. (기존 버튼 렌더는 삭제 예정)
// 버튼의 상태

enum class EButtonState
{
	Normal,
	Hovered,	// MouseEnter
	Pressed,	// MouseClick
	Disabled	// MoseExit
};

class NewButtonComponent : public UIComponent
{
public:
	NewButtonComponent() {}
	virtual ~NewButtonComponent() = default;

	void Create(GameObject* owner, std::unordered_map<EButtonState, std::shared_ptr<BitmapResource>>& bitmaps, RECT rect);

	virtual void Update() override;
	virtual void Render() override;
	virtual void OnEnable() override {}
	virtual void OnDestroy() override {}

	// 이벤트 처리는 람다로 호출하게 한다.
	void SetOnClick(std::function<void()> callback) { onClick = std::move(callback); }
	void SetOnHover(std::function<void()> callback) { onHover = std::move(callback); }
	void SetOnPress(std::function<void()> callback) { onPress = std::move(callback); }

private:
	void SetState(EButtonState state);
	bool HitTest(POINT pt) const;

	void HandleMouseEnter();
	void HandleMouseExit();
	void HandleMouseDown();
	void HandleMouseUp();

	EButtonState m_State = EButtonState::Normal;
	RECT m_rect{};
	POINT m_pt{};

	std::unordered_map<EButtonState, ID2D1Bitmap1*> m_bitmaps;

	//POINT m_pt;
	//RECT m_rect;

	std::function<void()> onClick;		// 누르고 떼야 실행
	std::function<void()> onPress;		// 누르자마자 실행
	std::function<void()> onHover;
};

