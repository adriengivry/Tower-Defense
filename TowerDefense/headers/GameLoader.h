#ifndef _GAMELOADER_
#define _GAMELOADER_

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>

#include "Slot.h"
#include "ActorsManager.h"
#include "GameInfo.h"
#include "UserInterface.h"

class GameLoader
{
public:
	explicit GameLoader(ActorsManager* p_actorManager = nullptr, GameInfo* p_gameInfo = nullptr, UserInterface* p_userInterface = nullptr);
	~GameLoader() {}

	ActorsManager* GetActorsManager() const { return m_actorsManager; }
	GameInfo* GetGameInfo() const { return m_gameInfo; }
	UserInterface* GetUserInterface() const { return m_userInterface; }

	void SetActorsManager(ActorsManager* p_value) { m_actorsManager = p_value; }
	void SetGameInfo(GameInfo* p_value) { m_gameInfo = p_value; }
	void SetUserInterface(UserInterface* p_value) { m_userInterface = p_value; }

	void AnalyseString(const std::string p_stringToAnalyse) const;

private:
	ActorsManager* m_actorsManager;
	GameInfo* m_gameInfo;
	UserInterface* m_userInterface;
};

#endif // !_GAMELOADER_