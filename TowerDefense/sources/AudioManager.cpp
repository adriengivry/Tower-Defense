#include "AudioManager.h"

AudioManager::AudioManager()
{
	m_engine = createIrrKlangDevice();

	if (!m_engine)
		std::cout << "ERROR LOADING AUDIO ENGINE" << std::endl;
}

AudioManager::~AudioManager()
{
	m_engine->drop();
}

void AudioManager::PlayRandomShot() const
{
	const int randomIndex = rand() % SHOT_SOUND_MAX + SHOT_SOUND_MIN;

	const std::string path(SHOT_SOUND_FOLDER + std::to_string(randomIndex) + SHOT_SOUND_EXTENSION);

	PLAY_SOUND(path)
}

void AudioManager::PlayRandomDeath() const
{
	const int randomIndex = rand() % DEATH_SOUND_MAX + DEATH_SOUND_MIN;

	const std::string path(DEATH_SOUND_FOLDER + std::to_string(randomIndex) + DEATH_SOUND_EXTENSION);

	PLAY_SOUND(path)
}

void AudioManager::PlayRandomMonsterVoice() const
{
	const int randomIndex = rand() % MONSTER_VOICE_SOUND_MAX + MONSTER_VOICE_SOUND_MIN;

	const std::string path(MONSTER_VOICE_SOUND_FOLDER + std::to_string(randomIndex) + MONSTER_VOICE_SOUND_EXTENSION);

	PLAY_SOUND(path)
}
