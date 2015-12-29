// My Game.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include "Classes.h"
#include "Config.h"
#include "InitiationGame.h"
#include "GamePlay.h"


using namespace sf;
using namespace std;


int main()
{	
	std::shared_ptr<PlayerConfig> player_config = std::make_shared<PlayerConfig>();
	std::shared_ptr<BonusConfig> bonus_config = std::make_shared<BonusConfig>();
	std::shared_ptr<Information> information = std::make_shared<Information>();
	std::shared_ptr<GameConfig> game = std::make_shared<GameConfig>();
	std::shared_ptr<NPCConfig> npc_config = std::make_shared<NPCConfig>();
	std::shared_ptr<Mission> mission = std::make_shared<Mission>();
	std::shared_ptr<Hero> hero = std::make_shared<Hero>();

	std::list<std::shared_ptr<Bonuses>> bonuses;
	std::list<std::shared_ptr<NonPlayer>> NPCs;

	InitGame(*game);
	InitBonuses(*game, *bonus_config, &bonuses);
	InitText(*information);
	InitNpc(*game, *npc_config, &NPCs);
	InitMisionScroll(*mission);
	InitPlayer(*player_config, *game, *hero);	
	StartGame(bonuses, NPCs, *player_config, *npc_config, *hero, *game);
	
	return 0;
}
