#pragma once
#include "Component.h"
#include "GameObject.h"
#include "SpriteLoader.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "Time.h"

class AnimatorComponent : public Component
{
public:
	void SetAnimationClip(AnimationClip* clip)
	{
		m_clip = clip;
		m_currentFrame = 0;
		m_elapsed = 0.0f;
	}

	void SetSpriteSheet(SpriteSheet* sheet)
	{
		m_spriteSheet = sheet;
		m_bitmap = ResourceManager::GetInstance().CreateBitmapResource("../Resource/" + m_spriteSheet->texture);
	}
	
	void Update() override
	{
		if (!m_clip || m_clip->frames.empty()) return;

		m_elapsed += Time::GetInstance().GetDeltaTime();

		if (m_elapsed >= m_clip->frames[m_currentFrame].duration)
		{
			m_currentFrame++;

			if (m_currentFrame >= m_clip->frames.size())
			{
				// Loop
				if (m_clip->loop) { m_currentFrame = 0; }

				// Non-Loop
				else { m_currentFrame = m_clip->frames.size() - 1; }

				m_elapsed = 0.0f;
			}
		}

		auto renderer = owner->GetComponent<SpriteRenderComponent>();
		
		if (!m_bitmap) return;
		
		if (renderer && m_spriteSheet)
		{
			const std::string& name = m_clip->frames[m_currentFrame].sprite;
			auto it = m_spriteSheet->spriteIndexMap.find(name);
			if (it != m_spriteSheet->spriteIndexMap.end())
			{
				const Sprite& sprite = m_spriteSheet->sprites[it->second];
				
				renderer->SetSpriteInfo(sprite, m_bitmap);
			}
		}
	}

	void OnEnable() override {}
	void OnDestroy() override {}

	const std::string& GetCurrentSpriteName() const
	{
		return m_clip->frames[m_currentFrame].sprite;
	}

	bool IsAnimationDone() const
	{
		if (!m_clip || m_clip->loop) return false;
		return m_currentFrame >= m_clip->frames.size() - 1;
	}

private:
	AnimationClip* m_clip = nullptr;
	std::shared_ptr<BitmapResource> m_bitmap;
	int m_currentFrame = 0;
	float m_elapsed = 0.0f;
	SpriteSheet* m_spriteSheet = nullptr;
};


