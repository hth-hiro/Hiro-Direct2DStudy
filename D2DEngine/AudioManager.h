#pragma once
#include "Singleton.h"
#include <fmod.hpp>
#pragma comment(lib, "fmod_vc.lib")

enum class AudioMode : uint32_t
{
	Loop = FMOD_LOOP_NORMAL | FMOD_2D,
	Default = FMOD_DEFAULT
};

class AudioManager : public Singleton<AudioManager>
{
	friend class Singleton<AudioManager>;

public:
	FMOD::System* m_System = nullptr;
	FMOD::Sound* m_Sound = nullptr;

	void Initialize();
	void Update();

	void LoadSound(
		const char* audioPath,
		AudioMode audioMode,
		FMOD::Sound** sound);

	void PlaySound(
		FMOD::Sound* sound,
		FMOD::Channel** channel,
		float volume = 1.0f,
		bool paused = false);	// true : 일시정지

	void PauseSound(
		FMOD::Channel* channel,
		bool paused = true
	);

	void ResumeSound(FMOD::Channel* channel);

	void StopSound(FMOD::Channel* channel);

	void Uninitialize();

	float GetMusicTime(FMOD::Channel* channel);

private:
	AudioManager() = default;
	~AudioManager() = default;

	bool isLoaded = false;
};