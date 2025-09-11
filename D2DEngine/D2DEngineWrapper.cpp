#include "pch.h"
#include <psapi.h>
#include "D2DEngineWrapper.h"
#include "Windows.h"
#include "InputSystem.h"
#include "Utils.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool g_bRenderMatrix = true;
bool g_bUnityCoords = true;
bool g_bMirror = false;

D2D1::Matrix3x2F g_matUnity = D2D1::Matrix3x2F::Identity();

void D2DEngineWrapper::Initialize()
{
	// 창 생성
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = m_WindowName.c_str();
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	RegisterClassEx(&wc);

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = { m_Width, m_Height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_hwnd = CreateWindowEx(
		0,
		m_WindowName.c_str(),
		m_TitleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL,
		NULL,
		m_hInstance,
		this // 인스턴스 주소를 NCREATESTRUCT의 lpCreateParams에 저장
	);
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	// 인풋 시스템 시작
	InputSystem::GetInstance().Startup(m_hwnd);

	// D3D 초기화
	D3D_FEATURE_LEVEL featureLevel;

	// Image Factory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(m_wicImagingFactory.GetAddressOf()));
	if (FAILED(hr)) return;

	// ID2D1Factory7 대신 ID2D1Factory3 사용
	ComPtr<ID2D1Factory3> d2dFactory3;
	D2D1_FACTORY_OPTIONS options = {};
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		__uuidof(ID2D1Factory3),
		&options,
		reinterpret_cast<void**>(d2dFactory3.GetAddressOf())
	);

	// DXGI SWAP CHAIN 초기화
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = 0; // 자동 설정
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

	// D3D11CreateDevice 대신 D3D11CreateDeviceAndSwapChain 사용
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		m_dxgiSwapChain.GetAddressOf(),
		m_d3dDevice.GetAddressOf(),
		&featureLevel,
		nullptr);
	if (FAILED(hr)) return;

	ComPtr<IDXGIDevice> dxgiDevice;
	hr = m_d3dDevice.As(&dxgiDevice);
	if (FAILED(hr)) return;

	ComPtr<ID2D1Device> d2dDevice;
	hr = d2dFactory3->CreateDevice(dxgiDevice.Get(), d2dDevice.GetAddressOf());
	if (FAILED(hr)) return;

	// ID2D1DeviceContext7 대신 ID2D1DeviceContext 사용
	ComPtr<ID2D1DeviceContext> d2dDeviceContext;
	hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, d2dDeviceContext.GetAddressOf());
	if (FAILED(hr)) return;

	// 멤버 변수에 안전하게 캐스팅해서 넣기
	hr = d2dDeviceContext.As(&m_d2dDeviceContext);
	if (FAILED(hr)) return;

	// 1. Swap Chain의 백버퍼를 얻는다
	ComPtr<IDXGISurface> dxgiBackBuffer;
	hr = m_dxgiSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	if (FAILED(hr)) return;

	// 2. Direct2D용 비트맵 생성 (렌더 타겟으로 쓸 것)
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	ComPtr<ID2D1Bitmap1> d2dTargetBitmap;
	hr = m_d2dDeviceContext->CreateBitmapFromDxgiSurface(dxgiBackBuffer.Get(), bitmapProperties, &d2dTargetBitmap);
	if (FAILED(hr)) return;

	// 3. 이 비트맵을 DeviceContext의 렌더 타겟으로 설정
	m_d2dDeviceContext->SetTarget(d2dTargetBitmap.Get());

	if (FAILED(hr)) return;
	m_initialized = true;

	// DirectWrite 팩터리를 만듭니다.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_DWriteFactory), reinterpret_cast<IUnknown**>(m_DWriteFactory.GetAddressOf()));
	assert(SUCCEEDED(hr));

	// DirectWrite 텍스트 형식 개체를 만듭니다.
	hr = m_DWriteFactory->CreateTextFormat(
		L"", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,   // Font Size
		L"", //locale
		m_DWriteTextFormat.GetAddressOf()
	);
	assert(SUCCEEDED(hr));

	hr = m_d2dDeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), m_pBrush.GetAddressOf());
	assert(SUCCEEDED(hr));

	ComPtr<IDXGIAdapter> dxgiAdapter;
	m_d3dDevice.As(&m_dxgiDevice);
	m_dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf());
	dxgiAdapter.As(&m_dxgiAdapter);

	// matCameraInv 초기화
	matCameraInv = D2D1::Matrix3x2F::Identity();

	
}

void D2DEngineWrapper::Update()
{

}

void D2DEngineWrapper::BeginDraw()
{
	m_d2dDeviceContext->BeginDraw();
}

void D2DEngineWrapper::Clear(const D2D1::ColorF& color)
{
	m_d2dDeviceContext->Clear(color);
}

void D2DEngineWrapper::DrawBitmapForTransform(ID2D1Bitmap1* bitmap, TransformComponent& transform, float opacity, const D2D1_RECT_F* srcRect, bool isUI)
{
	if (g_bUnityCoords)
		g_matUnity = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
		D2D1::Matrix3x2F::Translation(m_Width / 2.0f, m_Height / 2.0f);
	else
		g_matUnity = D2D1::Matrix3x2F::Identity();

	if (!opacity || opacity > 1.0f) opacity = 1.0f;
	if (opacity < 0.0f) opacity = 0.0f;

	D2D1_RECT_F newSrcRect = *srcRect;

	// Offset
	newSrcRect.top += 1;
	newSrcRect.bottom +=1;
	newSrcRect.left += 1;
	newSrcRect.right -= 1;

	if (m_d2dDeviceContext && (srcRect->left == 0 && srcRect->top == 0 && srcRect->right == 0 && srcRect->bottom == 0))
	{
		D2D1::Matrix3x2F matRender = MakeRenderMatrix(false, g_bUnityCoords, bitmap->GetSize().width / 2, bitmap->GetSize().height / 2);

		D2D1::Matrix3x2F matFinal;

		matFinal = matRender * transform.GetWorldMatrix();

		if (!isUI)
			matFinal = matFinal * matCameraInv;
		
		if (g_bUnityCoords)
			matFinal = matFinal * g_matUnity;

		m_d2dDeviceContext->SetTransform(matFinal);

		m_d2dDeviceContext->DrawBitmap(bitmap, nullptr, opacity);
	
	}
	else
	{
		D2D1::Matrix3x2F matRender = MakeRenderMatrix(false, g_bUnityCoords, (newSrcRect.right- newSrcRect.left) * 0.5f, (newSrcRect.bottom- newSrcRect.top) * 0.5f + 1);

		D2D1::Matrix3x2F matFinal;

		matFinal = matRender * transform.GetWorldMatrix();

		if (!isUI)
			matFinal = matFinal * matCameraInv;

		if (g_bUnityCoords)
			matFinal = matFinal * g_matUnity;

		m_d2dDeviceContext->SetTransform(matFinal);

		m_d2dDeviceContext->DrawBitmap(bitmap, nullptr, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &newSrcRect);
	}
}

void D2DEngineWrapper::DrawTextForTransform(const wchar_t* str, IDWriteTextFormat* textformat, float fontsize, D2D1::ColorF& color, TransformComponent& transform)
{
	float left = transform.GetTranslation().x;
	float top = transform.GetTranslation().y;
	float right = transform.GetTranslation().x + fontsize * 25;
	float bottom = transform.GetTranslation().y;

	m_DWriteTextFormat = textformat;

	m_pBrush.Get()->SetColor(color);

	m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Scale(fontsize,fontsize));
	m_d2dDeviceContext->DrawTextW(str, (UINT32)wcslen(str), m_DWriteTextFormat.Get(), D2D1::RectF(left, top, right, bottom), m_pBrush.Get());
}

//void D2DEngineWrapper::DrawBitmapForMatrix(ID2D1Bitmap1* bitmap, D2D1::Matrix3x2F& matrix)
//{
//	if (g_bUnityCoords)
//		g_matUnity = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
//		D2D1::Matrix3x2F::Translation(m_Width / 2.0f, m_Height / 2.0f);
//	else
//		g_matUnity = D2D1::Matrix3x2F::Identity();
//
//	if (m_d2dDeviceContext)
//	{
//		D2D1::Matrix3x2F matRender = MakeRenderMatrix(false, g_bUnityCoords, bitmap->GetSize().width / 2, bitmap->GetSize().height / 2);
//
//		D2D1::Matrix3x2F matFinal;
//		if (!g_bUnityCoords)
//			matFinal = matRender * matrix * matCameraInv;
//		else
//			matFinal = matRender * matrix * matCameraInv * g_matUnity;
//
//		m_d2dDeviceContext->SetTransform(matFinal);
//		m_d2dDeviceContext->DrawBitmap(bitmap);
//	}
//}

void D2DEngineWrapper::DrawRect(float left, float top, float right, float bottom, D2D1::ColorF color)
{
	if (!m_d2dDeviceContext) return;

	ID2D1SolidColorBrush* brush = nullptr;

	HRESULT hr = m_d2dDeviceContext->CreateSolidColorBrush(color, &brush);

	if (FAILED(hr) || !brush) return;

	D2D1_RECT_F rect = D2D1::RectF(left, top, right, bottom);

	//m_d2dDeviceContext->FillRectangle(rect, brush);
	m_d2dDeviceContext->DrawRectangle(rect, brush, 1.5f);
}

void D2DEngineWrapper::EndDraw()
{
	HRESULT hr = m_d2dDeviceContext->EndDraw();
	m_dxgiSwapChain->Present(1, 0);
} 

void D2DEngineWrapper::Uninitialize()
{
	if (m_d2dDeviceContext)
	{
		m_d2dDeviceContext->SetTarget(nullptr); // 백버퍼 참조 끊기
	}

	m_d2dDeviceContext = nullptr;
	m_d2dBitmapTarget = nullptr;
	m_dxgiSwapChain = nullptr;
	m_d3dDevice = nullptr;
	m_wicImagingFactory = nullptr;
	m_dxgiAdapter = nullptr;
	m_dxgiDevice = nullptr;
}

void D2DEngineWrapper::PrintMemoryUsage()
{
	int fontsize = 24;
	int left = 0;
	int top = 50;
	int right = left + 500;
	int bottom = top + 500;

	m_pBrush.Get()->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	
	DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
	m_dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);

	HANDLE hProcess = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS_EX pmc;
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	std::wstring VRAM = L"VRAM : " + FormatBytes(memInfo.CurrentUsage);

	GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	std::wstring DRAM = L"DRAM : " + FormatBytes(pmc.WorkingSetSize);
	std::wstring PageFile = L"PageFile : " + FormatBytes(pmc.PagefileUsage - pmc.WorkingSetSize);

	m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());
	m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Scale(fontsize, fontsize));
	m_d2dDeviceContext->DrawTextW(VRAM.c_str(), (UINT32)wcslen(VRAM.c_str()), m_DWriteTextFormat.Get(), D2D1::RectF(left, top, right, bottom), m_pBrush.Get());
	m_d2dDeviceContext->DrawTextW(DRAM.c_str(), (UINT32)wcslen(DRAM.c_str()), m_DWriteTextFormat.Get(), D2D1::RectF(left, top + 20, right, bottom), m_pBrush.Get());
	m_d2dDeviceContext->DrawTextW(PageFile.c_str(), (UINT32)wcslen(PageFile.c_str()), m_DWriteTextFormat.Get(), D2D1::RectF(left, top + 60, right, bottom), m_pBrush.Get());
}

HRESULT D2DEngineWrapper::CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap)
{
	ComPtr<IWICBitmapDecoder>     decoder;
	ComPtr<IWICBitmapFrameDecode> frame;
	ComPtr<IWICFormatConverter>   converter;

	HRESULT hr = m_wicImagingFactory->CreateDecoderFromFilename(
		path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr)) return hr;

	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr)) return hr;

	hr = m_wicImagingFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) return hr;

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);
	if (FAILED(hr)) return hr;

	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_NONE,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));

	// WIC 비트맵 -> Direct2D 비트맵으로 변환
	hr = D2DEngineWrapper::m_d2dDeviceContext->CreateBitmapFromWicBitmap(converter.Get(), &bmpProps, outBitmap);
	return hr;
}

D2D1::Matrix3x2F D2DEngineWrapper::MakeRenderMatrix(bool bMirror, bool bUnityCoords, float offsetX, float offsetY)
{
	if (!g_bRenderMatrix)
		return D2D1::Matrix3x2F::Identity();

	float scaleX = bMirror ? -1.0f : 1.0f;  // 이미지 좌우반전 이면 x축 반전
	float scaleY = bUnityCoords ? -1.0f : 1.0f; // 유니티 좌표계면 y축 상하 반전
	offsetX = bMirror ? offsetX : -offsetX; //  좌우반전일때 이미지 이동 값 처리
	offsetY = bUnityCoords ? offsetY : -offsetY; //  유니티 좌표계일때 이미지 이동 값 처리
	return D2D1::Matrix3x2F::Scale(scaleX, scaleY) * D2D1::Matrix3x2F::Translation(offsetX, offsetY);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// MouseWheel Check
	case WM_MOUSEWHEEL:
	{
		InputSystem::GetInstance().SetMouseWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam));

		break;
	}
	case WM_KEYDOWN:
		//if (wParam == VK_F2)
		//	g_bRenderMatrix = !g_bRenderMatrix;

		//if (wParam == VK_F3)
		//{
		//	g_bUnityCoords = !g_bUnityCoords;
		//}

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}