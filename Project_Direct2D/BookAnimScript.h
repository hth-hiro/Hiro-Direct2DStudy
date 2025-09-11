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

class BookAnimScript : public ScriptComponent
{
public:
	void Awake() override
	{
		LoadSpriteSheet("../Resource/json/Book_sprites.json", spriteSheet);
		LoadAnimationClip("../Resource/json/Book_Throw_anim.json", thrownClip, spriteSheet);
	}

	void Start() override
	{
		auto* tr = owner->GetComponent<TransformComponent>();
		tr->SetTranslation(0, 0);
		
		auto* sprite = owner->GetComponent<SpriteRenderComponent>();
		auto bitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/Book.png");
		sprite->SetBitmap(bitmap);

		m_animator = owner->GetComponent<AnimatorComponent>();
		m_animator->SetSpriteSheet(&spriteSheet);

		m_animator->SetAnimationClip(&thrownClip);
	}

	static AnimationClip thrownClip;
private:
	AnimatorComponent* m_animator = nullptr;
	SpriteSheet spriteSheet;
};

