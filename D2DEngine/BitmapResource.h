#pragma once
#include "framework.h"

class BitmapResource
{
public:
	bool LoadFromFile(const std::wstring& filePath);

	ID2D1Bitmap1* GetBitmap() const { return m_Bitmap.Get(); }

private:
	ComPtr<ID2D1Bitmap1> m_Bitmap;
};

