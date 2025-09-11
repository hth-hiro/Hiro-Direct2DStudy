#include "pch.h"
#include "BitmapResource.h"
#include "ResourceManager.h"

std::shared_ptr<BitmapResource> ResourceManager::CreateBitmapResource(const std::string& filepath)
{
    // Search key
    std::string key = filepath;
    auto it = m_mapBitmaps.find(key);
    if (it != m_mapBitmaps.end())
    {
        // weak_ptr -> shared_ptr
        if (!it->second.expired())
        {
            std::shared_ptr<BitmapResource> resourcePtr = it->second.lock();
            return resourcePtr;
        }
        else
        {
            m_mapBitmaps.erase(it);
        }
    }

    // 없거나 유효하지 않으면 새로 만든다.
    std::shared_ptr<BitmapResource> pResource = std::make_shared<BitmapResource>();

    std::wstring wpath(filepath.begin(), filepath.end());

    if (!pResource->LoadFromFile(wpath))// 내부에서 파일을 읽고 데이터를 생성한다.
    {
        return nullptr;
    }



    // 리소스 맵에 약한 참조 저장
    m_mapBitmaps[key] = pResource;

    return pResource;
}