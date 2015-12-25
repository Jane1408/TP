#pragma once
//#include "Config.h"
//#include "Struct.h"
#include <memory>



void InitMisionScroll(Mission & mission) {
	Image scroll_image;
	mission.t_scroll = std::make_shared<Texture>();
	mission.s_scroll = std::make_shared<Sprite>();
	scroll_image.loadFromFile("images/mission.png");
	mission.t_scroll->loadFromImage(scroll_image);
	mission.s_scroll->setTexture(*mission.t_scroll);
	mission.s_scroll->setTextureRect(IntRect(0, 0, MISSION_SCROLL_SIZE.x, MISSION_SCROLL_SIZE.y));
}

void InitBonuses(Level & lvl, BonusConfig & config, list<std::shared_ptr<Bonuses>> * bonuses) {
	std::vector<Object> bonus = lvl.GetObjects("bonus");
	for (int i = 0; i < bonus.size(); i++)
		bonuses->push_back(std::make_shared<Bonuses>(config, "Star", lvl, bonus[i].rect.left, bonus[i].rect.top, BONUS_SIZE.x, BONUS_SIZE.y));
}

void FindNpcPositions(Level & lvl, NPCConfig & config, list<std::shared_ptr<NonPlayer>> * NPCs) {
	std::vector<Object> all_obj;
	all_obj = lvl.GetAllObjects();
	string Name;
	string npc_check = "npc_";
	for (int i = 0; i < all_obj.size(); i++) {
		Name = "";
		if (all_obj[i].name.size() >= 4) {
			Name = all_obj[i].name;
			Name.erase(4, all_obj[i].name.size());
			if (Name == npc_check) {
				Name = all_obj[i].name;
				Name.erase(0, 4);
				config.position_npc.insert(pair<string, Vector2f>(Name, { all_obj[i].rect.left, all_obj[i].rect.top }));
				NPCs->push_back(std::make_shared<NonPlayer>(Name, config));

			}
		}
	}
}