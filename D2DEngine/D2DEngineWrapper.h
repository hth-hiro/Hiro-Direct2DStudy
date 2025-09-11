#pragma once
#include "framework.h"
#include <dwrite.h>
#include "TransformComponent.h"
#include "Singleton.h"

class D2DEngineWrapper : public Singleton<D2DEngineWrapper>
{
public:
    D2DEngineWrapper() = default;
    
    void Initialize();
    void Update();
    void BeginDraw();
    void Clear(const D2D1::ColorF& color);
    void DrawBitmapForTransform(ID2D1Bitmap1* bitmap, TransformComponent& transform, float opacity, const D2D1_RECT_F* srcRect, bool isUI);
    void DrawTextForTransform(const wchar_t* str, IDWriteTextFormat* textformat, float fontsize, D2D1::ColorF& color, TransformComponent& transform);
    //void DrawBitmapForMatrix(ID2D1Bitmap1* bitmap, D2D1::Matrix3x2F& matrix);
    void DrawRect(float left, float top, float right, float bottom, D2D1::ColorF color);
    void EndDraw();
    void Uninitialize();

    bool IsInitialized() const { return m_initialized; }

    void PrintMemoryUsage();

    bool m_Quit = false;

    // m_d2dDeviceContext를 갖고오는 Getter
    ComPtr<ID2D1DeviceContext7>& GetDC()
    {
        return m_d2dDeviceContext;
    }

    ComPtr<IDWriteFactory> GetDwriteFactory() const { return m_DWriteFactory; }

    HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap);

    D2D1::Matrix3x2F matCameraInv;

    ComPtr<IDXGIAdapter3> m_dxgiAdapter;
    ComPtr<IDXGIDevice3> m_dxgiDevice;

    // 창 크기
    UINT            m_Width = 1920;
    UINT            m_Height = 1080;
    HWND            m_hwnd = nullptr;
private:
    bool m_initialized = false;

    HRESULT         hr;
    HINSTANCE		m_hInstance;

    std::wstring	m_WindowName = L"D2DEngine";
    std::wstring	m_TitleName = L"한글 테스트";     // 이게 창 이름임
    std::string		m_ModulePath;
    std::string		m_WorkingPath;

    ComPtr<ID2D1DeviceContext7> m_d2dDeviceContext;
    ComPtr<IDXGISwapChain> m_dxgiSwapChain;
    ComPtr<ID3D11Device> m_d3dDevice;
    ComPtr<ID2D1Bitmap1> m_d2dBitmapTarget;
    ComPtr<IWICImagingFactory> m_wicImagingFactory;
    ComPtr<IDWriteFactory> m_DWriteFactory;
    ComPtr<IDWriteTextFormat> m_DWriteTextFormat;
    ComPtr<ID2D1SolidColorBrush> m_pBrush;


    D2D1::Matrix3x2F MakeRenderMatrix(bool bMirror, bool bUnityCoords, float offsetX, float offsetY);
};