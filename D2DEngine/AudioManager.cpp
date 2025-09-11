#include "pch.h"
#include "AudioManager.h"

void AudioManager::Initialize()
{
	if (isLoaded) return;

	FMOD_RESULT fr = FMOD::System_Create(&m_System);

	if (fr != FMOD_OK) return;
		
	fr = m_System->init(512, FMOD_INIT_NORMAL, nullptr);
}

void AudioManager::Update()
{
	m_System->update();
}

void AudioManager::LoadSound(const char* audioPath, AudioMode audioMode, FMOD::Sound** sound)
{
	FMOD_RESULT fr = m_System->createSound(audioPath, /*static_cast<FMOD_MODE>(audioMode)*/FMOD_DEFAULT, nullptr, sound);
	if (fr != FMOD_OK)
	{
		return;
	}

	m_Sound = *sound;
	
	isLoaded = true;
}

void AudioManager::PlaySound(FMOD::Sound* sound, FMOD::Channel** channel, float volume, bool paused)
{
	if (!sound || !channel) return;

	if (volume > 1.0f) volume = 1.0f;
	if (volume < 0.0f) volume = 0.0f;

	FMOD_RESULT fr = m_System->playSound(sound, nullptr, paused, channel);

	if (fr != FMOD_OK) return;

	if (*channel) (*channel)->setVolume(volume);
}

void AudioManager::PauseSound(FMOD::Channel* channel, bool paused)
{
	if (channel) channel->setPaused(paused);
}

void AudioManager::ResumeSound(FMOD::Channel* channel)
{
	PauseSound(channel, false);
}

void AudioManager::StopSound(FMOD::Channel* channel)
{
	if (channel) channel->stop();
}

void AudioManager::Uninitialize()
{
	if (m_Sound) m_Sound->release();
	if (m_System)
	{
		m_System->close();
		m_System->release();
	}

	isLoaded = false;
}

float AudioManager::GetMusicTime(FMOD::Channel* channel)
{
	if (!channel) return 0.0f;

	unsigned int time = 0;
	FMOD_RESULT result = channel->getPosition(&time, FMOD_TIMEUNIT_MS);

	if (result == FMOD_OK)
	{
		return static_cast<float>(time) / 1000.0f;	// 밀리초 단위 -> 초 단위
	}

	return 0.0f;
}
