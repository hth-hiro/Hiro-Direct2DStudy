#pragma once
#include "pch.h"
#include <unordered_map>
#include "Sprite.h"

struct SpriteSheet
{
	std::string texture;
	float textureWidth, textureHeight;
	std::vector<Sprite> sprites;
	std::unordered_map<std::string, int> spriteIndexMap;
};