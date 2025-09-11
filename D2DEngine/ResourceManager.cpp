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

    // ���ų� ��ȿ���� ������ ���� �����.
    std::shared_ptr<BitmapResource> pResource = std::make_shared<BitmapResource>();

    std::wstring wpath(filepath.begin(), filepath.end());

    if (!pResource->LoadFromFile(wpath))// ���ο��� ������ �а� �����͸� �����Ѵ�.
    {
        return nullptr;
    }



    // ���ҽ� �ʿ� ���� ���� ����
    m_mapBitmaps[key] = pResource;

    return pResource;
}