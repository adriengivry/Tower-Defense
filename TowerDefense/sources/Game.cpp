#include "Game.h"

Game::Game()
{
	m_audioManager = new AudioManager;
	m_gameInfo = new GameInfo(m_audioManager);
	m_sdlManager = new SDLManager;
	m_window = new Window;
	m_eventManager = new EventManager;
	m_userInterface = new UserInterface(GetWindow(), GetGameInfo());
	m_actorManager = new ActorsManager(GetWindow(), GetEventManager(), GetGameInfo(), GetUserInterface());
	m_gameLoader = new GameLoader(GetActorsManager(), GetGameInfo(), GetUserInterface());
	
	srand(static_cast<int>(time(nullptr)));
}

Game::~Game()
{
	delete GetActorsManager();
	delete GetUserInterface();
	delete GetEventManager();
	delete GetWindow();
	delete GetGameInfo();
	delete GetSDLManager();
	delete GetAudioManager();
}

void Game::CheckEvents() const
{
	if (GetEventManager()->GetEvent(EXIT_EVENT).IsOn())
		GetGameInfo()->SetRun(false);

	if (GetEventManager()->GetEvent(SKIP_PREP_EVENT).IsOn())
	{
		if (!GetGameInfo()->IsCurrentStageCompleted() && GetGameInfo()->GetTickCounter() < 1200)
		{
			GetGameInfo()->SetTickCounter(1199);
			GetGameInfo()->AddToElapsed(20 - GetGameInfo()->GetElapsedTime());
			GetEventManager()->GetEvent(SKIP_PREP_EVENT).Toggle();
			GetGameInfo()->SetCanSpawn(true);
		}
	}

	if (GetGameInfo()->GetGameState() == GameState::STATE_PLAY)
		if (GetEventManager()->GetEvent(PAUSE_EVENT).IsOn())
			GetGameInfo()->SetGameState(GameState::STATE_PAUSE);
	
	if (GetGameInfo()->GetGameState() == GameState::STATE_PAUSE)
		if (GetEventManager()->GetEvent(GameState::STATE_PAUSE).IsOff())
		{
			GetGameInfo()->SetThisTime(SDL_GetTicks());
			GetGameInfo()->SetLastTime(SDL_GetTicks());
			GetGameInfo()->SetDeltaTime(0);
			GetGameInfo()->SetGameState(GameState::STATE_PLAY);
		}
}

void Game::Setup() const
{
	GetAudioManager()->PlayMusic(BACKGROUND_MUSIC_PATH);
	GetAudioManager()->PlayAmbiant(WIND_SOUND_PATH);
}

void Game::PauseTick() const
{
	GetUserInterface()->SetCurrentFont(BIG_FONT);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->SetAlign(ALIGN_CENTER);
	GetUserInterface()->ShowText("GAME PAUSED", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::DefeatTick() const
{
	GetUserInterface()->SetCurrentFont(BIG_FONT);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->SetAlign(ALIGN_CENTER);
	GetUserInterface()->ShowText("GAME OVER", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 30);
	GetUserInterface()->ShowText("Stage reached : " + std::to_string(GetGameInfo()->GetStage()), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 30);
}

void Game::PlayTick() const
{
	GetGameInfo()->CheckCastleLife();

	GetGameInfo()->IncrementTickCounter();
	GetGameInfo()->SetLastTime(GetGameInfo()->GetThisTime());
	GetGameInfo()->SetThisTime(SDL_GetTicks());
	GetGameInfo()->SetDeltaTime(static_cast<float>(GetGameInfo()->GetThisTime() - GetGameInfo()->GetLastTime()) / 1000.f);
	GetGameInfo()->AddToElapsed(GetGameInfo()->GetDeltaTime());

	if (GetGameInfo()->IsCurrentStageCompleted())
	{
		GetUserInterface()->ShowImportantText("STAGE CLEAR! +" + std::to_string(static_cast<int>(MONEY_AFTER_WAVE_CLEAR * (GetGameInfo()->GetStage() + 1) / 2.f)) + "$");
		if (GetGameInfo()->GetTickCounter() >= 200)
		{
			GetActorsManager()->ClearEnemies();
			GetGameInfo()->SetCurrentStageCompleted(false);
			GetGameInfo()->ResetTickCounter();
			GetGameInfo()->SetTimer(PREPARATION_TIME);
		}

		GetUserInterface()->ShowWaveClearScore();

		return;
	}


	if (ElapsedIsBetween(0, 2))
	{
		GetGameInfo()->SetCurrentStageCompleted(false);
		GetUserInterface()->ShowImportantText("PREPARE THE BATTLEFIELD");
	}

	if (ElapsedIsBetween(PREPARATION_TIME, PREPARATION_TIME + 2))
	{
		GetUserInterface()->ShowImportantText("DEFEND YOUR CASTLE!");
	}
	
	if (ElapsedIs(PREPARATION_TIME))
	{
		GetAudioManager()->PlaySound(WAVE_START_SOUND_PATH);
		GetGameInfo()->SetCanSpawn(true);
		GetGameInfo()->AddTimer(WAVE_DURATION);
	}

	int timeRemaining = static_cast<int>(GetGameInfo()->GetTimer() - GetGameInfo()->GetElapsedTime());
	if (timeRemaining <= 0)
		timeRemaining = 0;

	std::string timeRemaining_str = std::to_string(timeRemaining);

	if (timeRemaining < 10)
		timeRemaining_str = "0" + timeRemaining_str;
		
	if (timeRemaining > 0)
		GetUserInterface()->ShowTimer("00:" + timeRemaining_str);
	else
		GetUserInterface()->ShowTimer("Time is up");


	if (GetGameInfo()->CanSpawn())
	{
		int stage = GetGameInfo()->GetStage();
		if (stage > 20)
			stage = 20;
			
		if (ToDoEveryXTicks(300 - stage * 8))
		{
			if (random_between(1,5) != 1)
				GetActorsManager()->SpawnRandomEnemy();
		}
	}

	if (ElapsedIsSuperior(PREPARATION_TIME + WAVE_DURATION))
	{
		GetGameInfo()->SetCanSpawn(false);
		if (GetActorsManager()->HowManyAliveEnemy() == 0)
		{
			GetGameInfo()->NextStage();
			GetGameInfo()->ResetTickCounter();
			GetAudioManager()->PlaySound(WAVE_CLEAR_SOUND_PATH);
		}
	}
}

uint8_t Game::Run() const
{
	Setup();

	while (GetGameInfo()->IsRunning())
	{
		switch (GetGameInfo()->GetGameState())
		{
		default:
		case GameState::STATE_PLAY:
			GetEventManager()->UpdateEvents();
			CheckEvents();
			GetActorsManager()->UpdateActors();
			Tick();
			GetUserInterface()->Update();
			GetWindow()->UpdateRenderer();
			GetWindow()->ClearScreen();
			break;

		case GameState::STATE_PAUSE:
			GetEventManager()->UpdateEvents();
			CheckEvents();
			Tick();
			GetWindow()->UpdateRenderer();
			GetWindow()->ClearScreen();
			break;

		case GameState::STATE_DEFEAT:
			GetEventManager()->UpdateEvents();
			CheckEvents();
			Tick();
			GetWindow()->UpdateRenderer();
			GetWindow()->ClearScreen();
			break;
		}
		SDL_Delay(static_cast<Uint32>(1000.f / GAME_FRAMERATE));
	}
	return EXIT_SUCCESS;
}

void Game::Tick() const
{
	switch(GetGameInfo()->GetGameState())
	{
	default:
	case GameState::STATE_PLAY:
		PlayTick();
		break;

	case GameState::STATE_PAUSE:
		PauseTick();
		break;

	case GameState::STATE_DEFEAT:
		DefeatTick();
		break;
	}
}
