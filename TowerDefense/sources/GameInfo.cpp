#include "GameInfo.h"

GameInfo::GameInfo(AudioManager* p_audioManager)
{
	SetRun(true);
	SetCanSpawn(false);
	SetCurrentStageCompleted(false);

	SetGameState(GameState::STATE_PLAY);
	SetAudioManager(p_audioManager);

	SetMoney(STARTING_MONEY);
	SetStage(STARTING_STAGE);
	SetCastleMaxLife(CASTLE_LIFE);
	m_castleLife = CASTLE_LIFE;

	SetTickCounter(STARTING_TICK);

	SetSelectedTower(0);
	SetThisTime(0);
	SetLastTime(0);
	SetDeltaTime(0);

	SetTimer(PREPARATION_TIME);
}

void GameInfo::SetCastleLife(const size_t p_value)
{
	if (p_value > m_castleLife)
		m_castleLife = 0;
	else
		m_castleLife = p_value;
}

void GameInfo::RemoveCastleLife(const int p_value)
{
	SetCastleLife(GetCastleLife() - p_value);
}

void GameInfo::NextStage()
{
	SetStage(GetStage() + 1);
	AddMoney(static_cast<int>(MONEY_AFTER_WAVE_CLEAR * (GetStage() + 1) / 2.f));
	SetCurrentStageCompleted(true);
}

void GameInfo::CheckCastleLife()
{
	if (GetCastleLife() == 0)
	{
		SetGameState(GameState::STATE_DEFEAT);
		GetAudioManager()->StopSounds();
		GetAudioManager()->PlaySound(GAME_OVER_SOUND_PATH);
	}
}
