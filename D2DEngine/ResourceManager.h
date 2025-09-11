#pragma once
#include "Singleton.h"
#include <unordered_map>

class BitmapResource;
class ResourceManager : public Singleton<ResourceManager>
{
public:
	std::shared_ptr<BitmapResource> CreateBitmapResource(const std::string& path);

private:
	std::unordered_map<std::string, std::weak_ptr<BitmapResource>> m_mapBitmaps;
};