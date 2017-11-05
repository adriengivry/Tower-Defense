#ifndef _AUDIOMANAGER_
#define _AUDIOMANAGER_

#include <iostream>
#include <string>
#include <irrKlang.h>

#include <SDL.h>

#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;

#define BACKGROUND_MUSIC_PATH "assets/audio/musics/background.ogg"

#define WIND_SOUND_PATH "assets/audio/ambiant/wind.ogg"

#define COIN_SOUND_PATH "assets/audio/sounds/coin.ogg"
#define CASTLE_TOWER_CREATE_SOUND_PATH "assets/audio/sounds/castle_tower_create.ogg"
#define ARCHER_TOWER_CREATE_SOUND_PATH "assets/audio/sounds/archer_tower_create.ogg"
#define CASTLE_TOWER_UPGRADE_SOUND "assets/audio/sounds/castle_tower_upgrade.ogg"
#define ARCHER_TOWER_UPGRADE_SOUND "assets/audio/sounds/archer_tower_upgrade.ogg"
#define DESTROY_TOWER_SOUND_PATH "assets/audio/sounds/destroy_tower.ogg"
#define WAVE_CLEAR_SOUND_PATH "assets/audio/sounds/wave_clear.ogg"
#define TOWER_SHOT_SOUND_PATH "assets/audio/sounds/tower_shot.ogg"
#define BREAK_SHIELD_SOUND_PATH "assets/audio/sounds/break_shield.ogg"
#define SHIELD_BLOCK_SOUND_PATH "assets/audio/sounds/shield_block.ogg"
#define WAVE_START_SOUND_PATH "assets/audio/sounds/wave_start.ogg"
#define CLICK_SOUND_PATH "assets/audio/sounds/click.ogg"
#define ERROR_SOUND_PATH "assets/audio/sounds/error.ogg"
#define INTO_CASTLE_SOUND_PATH "assets/audio/sounds/into_castle.ogg"
#define GAME_OVER_SOUND_PATH "assets/audio/sounds/game_over.ogg"

#define SHOT_SOUND_FOLDER "assets/audio/sounds/arrow_shots/shot_"
#define SHOT_SOUND_EXTENSION ".ogg"
#define SHOT_SOUND_MIN 1
#define SHOT_SOUND_MAX 8

#define DEATH_SOUND_FOLDER "assets/audio/sounds/death/death_"
#define DEATH_SOUND_EXTENSION ".mp3"
#define DEATH_SOUND_MIN 1
#define DEATH_SOUND_MAX 19

#define MONSTER_VOICE_SOUND_FOLDER "assets/audio/sounds/monster_voices/monster-"
#define MONSTER_VOICE_SOUND_EXTENSION ".ogg"
#define MONSTER_VOICE_SOUND_MIN 1
#define MONSTER_VOICE_SOUND_MAX 18

#define PLAY_MUSIC(path) m_engine->play2D(path.c_str(), true);
#define PLAY_AMBIANT(path) m_engine->play2D(path.c_str(), true);
#define PLAY_SOUND(path) m_engine->play2D(path.c_str(), false);

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlayMusic(std::string p_path) const { PLAY_MUSIC(p_path) }
	void PlayAmbiant(std::string p_path) const { PLAY_AMBIANT(p_path) }
	void PlaySound(std::string p_path) const { PLAY_SOUND(p_path) }

	void PlayRandomShot() const;
	void PlayRandomDeath() const;
	void PlayRandomMonsterVoice() const;

	void StopSounds() const { m_engine->stopAllSounds(); }

	ISoundEngine* GetEngine() const { return m_engine; }

private:
	ISoundEngine* m_engine;
};

#endif // !_AUDIOMANAGER_