#pragma once
#include <string>
#include <dwrite.h>
#include <psapi.h>
#include "RenderComponent.h"
#include "GameObject.h"
#include "Utils.h"

class TextRenderComponent:
	public RenderComponent
{	
public:
	TextRenderComponent();
	virtual ~TextRenderComponent();
	
	void SetText(
		const std::wstring& text,
		const std::wstring& fontName = L"Arial",
		float size = 24.0f,
		const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::White)
	);

	std::wstring UpdateMemoryInfo();

	virtual void Render() override;

	float GetTextHeight() const;
	float GetTextWidth() const;

private:
	void PrintMemoryUsage(
		const std::wstring& fontName = L"Arial",
		float size = 24.0f,
		const D2D1::ColorF& color = D2D1::ColorF(D2D1::ColorF::White)
	);
	std::wstring m_text = L"";
	D2D1::ColorF m_color = D2D1::ColorF(D2D1::ColorF::White);
	float m_fontSize = 24.0f;
	std::wstring m_fontName = L"Arial";

	IDWriteTextLayout* m_pTextLayout;
	ComPtr<IDWriteTextFormat> m_TextFormat;
	ComPtr<ID2D1SolidColorBrush> m_TextBrush;
};