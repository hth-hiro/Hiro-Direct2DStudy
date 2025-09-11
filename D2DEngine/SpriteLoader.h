#pragma once
#include "json.hpp"	// ������ json ���̺귯���� �־����� ����� �߰�
#include "Sprite.h"
#include "SpriteSheet.h"
#include "AnimationClip.h"

using json = nlohmann::json;

//... �Լ� ����
// SpriteShheet JSON -> SpriteSheet Class
void LoadSpriteSheet(const std::string& filePath, SpriteSheet& spriteSheet);

// AnimationClip JSON -> AnimationClip Class ,   FrameInfo�� �̸����� Index�� �����ϱ����� SpriteSheet �� �ʿ��ϴ�.
void LoadAnimationClip(const std::string& filePath, AnimationClip& clip, const SpriteSheet& SpriteSheet);