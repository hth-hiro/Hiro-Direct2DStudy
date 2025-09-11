#include "pch.h"
#include "BitmapResource.h"
#include "D2DEngineWrapper.h"

bool BitmapResource::LoadFromFile(const std::wstring& filePath)
{
    ID2D1Bitmap1* rawBitmap = nullptr;

    HRESULT hr = D2DEngineWrapper::GetInstance().CreateBitmapFromFile(filePath.c_str(), &rawBitmap);

    if (FAILED(hr) || rawBitmap == nullptr)
    {
        return false;
    }

    m_Bitmap.Reset();
    m_Bitmap.Attach(rawBitmap);
    return true;
}
