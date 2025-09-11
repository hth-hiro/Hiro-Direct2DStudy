#pragma once
#include "json.hpp"	// 엔진에 json 라이브러리를 넣었으니 헤더에 추가
#include "Sprite.h"
#include "SpriteSheet.h"
#include "AnimationClip.h"

using json = nlohmann::json;

//... 함수 구현
// SpriteShheet JSON -> SpriteSheet Class
void LoadSpriteSheet(const std::string& filePath, SpriteSheet& spriteSheet);

// AnimationClip JSON -> AnimationClip Class ,   FrameInfo의 이름으로 Index를 설정하기위해 SpriteSheet 가 필요하다.
void LoadAnimationClip(const std::string& filePath, AnimationClip& clip, const SpriteSheet& SpriteSheet);