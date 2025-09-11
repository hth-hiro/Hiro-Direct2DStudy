#pragma once
#include "pch.h"

struct FrameInfo
{
	std::string sprite;
	int spriteSheetIndex;
	float duration;
};

struct EventInfo
{
	std::string function;
	std::string parameter;
	float time;
};

struct AnimationClip
{
	std::string clipName;
	std::string texturePath;
	bool loop;
	float duration;
	std::vector<FrameInfo> frames;
	std::vector<EventInfo> events;
};