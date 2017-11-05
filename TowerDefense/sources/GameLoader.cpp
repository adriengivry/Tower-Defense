#include "GameLoader.h"

GameLoader::GameLoader(ActorsManager* p_actorsManager, GameInfo* p_gameInfo, UserInterface* p_userInterface)
{
	SetActorsManager(p_actorsManager);
	SetGameInfo(p_gameInfo);
	SetUserInterface(p_userInterface);

	std::ifstream configFile;
	std::string currentLine;

	configFile.open(CONFIG_PATH);
	if (!configFile.is_open())
		std::cout << "Config file failed to open file" << std::endl;

	std::getline(configFile, currentLine);
	std::getline(configFile, currentLine);

	while (std::getline(configFile, currentLine))
	{
		AnalyseString(currentLine);
	}

	configFile.close();

}


void GameLoader::AnalyseString(const std::string p_stringToAnalyse) const
{
	if (p_stringToAnalyse == "")
		return;

	if (!(p_stringToAnalyse.find(",") != std::string::npos))
		return;

	if (p_stringToAnalyse.find("//") != std::string::npos)
		return;

	std::vector<std::string> actorInfo;

	std::istringstream iss(p_stringToAnalyse);

	for (std::string token; std::getline(iss, token, ','); )
		actorInfo.push_back(std::move(token));

	if (actorInfo[0] == "slot")
	{
		Slot* toAdd = new Slot(GetActorsManager()->GetWindow(), GetGameInfo());
		toAdd->SetPosition(static_cast<float>(atoi(actorInfo[1].c_str())), static_cast<float>(atoi(actorInfo[2].c_str())));
		toAdd->SetEnemyList(&GetActorsManager()->GetEnemies());
		toAdd->SetUserInterface(GetUserInterface());
		toAdd->SetProjectileList(&GetActorsManager()->GetProjectiles());
		toAdd->SetTowerList(&GetActorsManager()->GetTowers());
		GetActorsManager()->GetSlots().push_back(toAdd);
	}
}

