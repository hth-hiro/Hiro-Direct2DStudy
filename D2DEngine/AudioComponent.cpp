#include "pch.h"
#include "AudioComponent.h"

void AudioComponent::Init()
{
	AudioManager::GetInstance().Initialize();

	m_Channel = nullptr;
}

void AudioComponent::Load(const char* audioPath, AudioMode audioMode)
{
	AudioManager::GetInstance().LoadSound(audioPath, audioMode, &m_Sound);
}

void AudioComponent::Play(float volume, bool paused)
{
	if (!m_Sound) return;

	AudioManager::GetInstance().PlaySound(m_Sound, &m_Channel, volume, paused);
}

void AudioComponent::Pause(bool paused)
{
	AudioManager::GetInstance().PauseSound(m_Channel, paused);
}

void AudioComponent::Resume()
{
	AudioManager::GetInstance().ResumeSound(m_Channel);
}

void AudioComponent::Stop()
{
	AudioManager::GetInstance().StopSound(m_Channel);
}

float AudioComponent::GetPlayTime() const
{
	return AudioManager::GetInstance().GetMusicTime(m_Channel);
}
