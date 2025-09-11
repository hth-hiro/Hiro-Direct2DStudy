#pragma once
#include "Component.h"
#include "AudioManager.h"

class AudioComponent : public Component
{
public:
	AudioComponent() {}
	virtual ~AudioComponent() = default;

	virtual void Awake() override {}
	virtual void Start() override {}
	virtual void Update() override {}

	void Init();

	void Load(
		const char* audioPath,
		AudioMode audioMode);

	void Play(
		float volume = 1.0f,
		bool paused = false);

	void Pause(bool paused = true);

	void Resume();

	void Stop();

	float GetPlayTime() const;

	virtual void OnEnable() {}
	virtual void OnDestroy() {}

private:
	FMOD::Sound* m_Sound = nullptr;
	FMOD::Channel* m_Channel = nullptr;
	bool isLoaded = false;
};

