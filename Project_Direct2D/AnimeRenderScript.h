#pragma once
// base
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/ScriptComponent.h"
#include "../D2DEngine/TransformComponent.h"
#include "../D2DEngine/SpriteRenderComponent.h"
#include "../D2DEngine/ResourceManager.h"

// for animation
#include "../D2DEngine/SpriteSheet.h"
#include "../D2DEngine/AnimationClip.h"
#include "../D2DEngine/SpriteLoader.h"
#include "../D2DEngine/AnimatorComponent.h"

class AnimeRenderScript : public ScriptComponent
{
public:
	void Awake() override
	{
		LoadSpriteSheet("../Resource/json/Girl_sprites.json", spriteSheet);
		LoadAnimationClip("../Resource/json/Girl_Attack_anim.json", attackClip, spriteSheet);
		LoadAnimationClip("../Resource/json/Girl_Walk_anim.json", walkClip, spriteSheet);
		LoadAnimationClip("../Resource/json/Girl_Idle_anim.json", idleClip, spriteSheet);
	}

	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(0, 0);
		tr->SetScale(2.0f, 2.0f);

		auto* sprite = owner->GetComponent<SpriteRenderComponent>();
 		auto bitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Girl.png");
		sprite->SetBitmap(bitmap);

		m_animator = owner->GetComponent<AnimatorComponent>();
		m_animator->SetSpriteSheet(&spriteSheet);

		// Idle
		m_animator->SetAnimationClip(&idleClip);
	}

	static AnimationClip attackClip;
	static AnimationClip walkClip;
	static AnimationClip idleClip;
private:
	AnimatorComponent* m_animator = nullptr;
	SpriteSheet spriteSheet;
};

