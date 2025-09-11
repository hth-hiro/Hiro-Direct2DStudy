#include <float.h>
#include "pch.h"
#include "TextRenderComponent.h"
#include "D2DEngineWrapper.h"

TextRenderComponent::TextRenderComponent()
{

}

TextRenderComponent::~TextRenderComponent()
{
	
}

void TextRenderComponent::SetText(const std::wstring& text,
	const std::wstring& fontName,
	float size,
	const D2D1::ColorF& color
)
{
	m_text = text;
	m_fontName = fontName;
	m_fontSize = size;		// / 2.5f
	m_color = color;

	HRESULT hr = D2DEngineWrapper::GetInstance().GetDwriteFactory()->CreateTextFormat(
		m_fontName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_fontSize,
		L"ko-kr", // locale
		&m_TextFormat
	);

	hr = D2DEngineWrapper::GetInstance().GetDwriteFactory()->CreateTextLayout(
		m_text.c_str(),
		static_cast<UINT32>(m_text.length()), 
		m_TextFormat.Get(),
		FLT_MAX,
		FLT_MAX,  
		&m_pTextLayout   
	);
	
	if (FAILED(hr))
	{
		// 에러 처리
		m_TextFormat.Reset();
	}

	// 브러시 생성: 나중에 Render에서 한 번만 생성해도 됨
	auto d2dContext = D2DEngineWrapper::GetInstance().GetDC();
	if (d2dContext)
	{
		hr = d2dContext->CreateSolidColorBrush(m_color, &m_TextBrush);
		if (FAILED(hr))
		{
			m_TextBrush.Reset();
		}
	}
}

void TextRenderComponent::PrintMemoryUsage(const std::wstring& fontName, float size, const D2D1::ColorF& color)
{
	DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
	D2DEngineWrapper::GetInstance().m_dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);

	HANDLE hProcess = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	std::wstring VRAM = L"VRAM : " + FormatBytes(memInfo.CurrentUsage);

	GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	std::wstring DRAM = L"DRAM : " + FormatBytes(pmc.WorkingSetSize);

	int diff = 0;
	std::wstring PageFile = L"PageFile : ";
	diff = pmc.PagefileUsage - pmc.WorkingSetSize;
	if (diff < 0) PageFile = L"PageFile : " + FormatBytes(pmc.PagefileUsage);
	else PageFile = L"PageFile : " + FormatBytes(diff);

	m_text = VRAM + L"\n" + DRAM + L"\n" + PageFile;

	m_fontName = fontName;
	m_fontSize = size;
	m_color = color;

	HRESULT hr = D2DEngineWrapper::GetInstance().GetDwriteFactory()->CreateTextFormat(
		m_fontName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_fontSize,
		L"ko-kr", // locale
		&m_TextFormat
	);

	hr = D2DEngineWrapper::GetInstance().GetDwriteFactory()->CreateTextLayout(
		m_text.c_str(),
		static_cast<UINT32>(m_text.length()),
		m_TextFormat.Get(),
		FLT_MAX,
		FLT_MAX,
		&m_pTextLayout
	);

	if (FAILED(hr))
	{
		// 에러 처리
		m_TextFormat.Reset();
	}

	// 브러시 생성: 나중에 Render에서 한 번만 생성해도 됨
	auto d2dContext = D2DEngineWrapper::GetInstance().GetDC();
	if (d2dContext)
	{
		hr = d2dContext->CreateSolidColorBrush(m_color, &m_TextBrush);
		if (FAILED(hr))
		{
			m_TextBrush.Reset();
		}
	}
}

std::wstring TextRenderComponent::UpdateMemoryInfo()
{
	PrintMemoryUsage(m_fontName, m_fontSize, m_color);

	return m_text;
}

// 뭔가 텍스트 정렬 관련 함수 추가하면 좋을거 같음
// 좌우 정렬(offset) 상하정렬(offset)
// fontsize 별로 가운데 정렬하게끔

void TextRenderComponent::Render()
{
	auto d2dContext = D2DEngineWrapper::GetInstance().GetDC();
	if (!d2dContext) return;

	if (m_text.empty()) return;

	if (!m_TextFormat) return;

	if (!m_TextBrush) return;

	// 그릴 영역 - Transform 위치 기준으로 정하면 됨
	TransformComponent* transform = owner->GetTransform();
	if (!transform) return;

	D2D1_POINT_2F pos = D2D1::Point2F(transform->GetTranslation().x, transform->GetTranslation().y);

	D2DEngineWrapper::GetInstance().DrawTextForTransform(m_text.c_str(), m_TextFormat.Get(), m_fontSize,  m_color, *transform );
}

float TextRenderComponent::GetTextHeight() const
{
	//return ( 150 / m_fontSize ) - 5;

	// 기본 라인 높이: fontSize 기준 비례값
	float lineHeight = m_fontSize * 2.4f;

	// 줄 개수 계산: \n 기준으로 +1
	size_t lineCount = std::count(m_text.begin(), m_text.end(), L'\n') + 1;

	return lineHeight * static_cast<float>(lineCount);
}

float TextRenderComponent::GetTextWidth() const
{
	return 0.0f;
}
