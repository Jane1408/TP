#include "stdafx.h"
#include "Struct.h"
#include "ClassBonuses.h"
#include "ClassNonPlayer.h"
#include "ClassPlayer.h"
#include "Config.h"
#include "InitiationGame.h"
#include <memory>


using namespace sf;
using namespace std;

void InitMisionScroll(Mission & mission) {
	
	mission.img_scroll.loadFromFile("images/mission.png");
	mission.t_scroll = std::make_shared<Texture>();
	mission.s_scroll = std::make_shared<Sprite>();
	mission.t_scroll->loadFromImage(mission.img_scroll);
	mission.s_scroll->setTexture(*mission.t_scroll);
	mission.s_scroll->setTextureRect(IntRect(0, 0, mission.scroll_size.x, mission.scroll_size.y));
}

void InitGame(GameConfig & game) {
	game.window = std::make_shared<RenderWindow>(sf::VideoMode(640, 480), game.name_game);
	game.lvl = std::make_shared<Level>();
	game.lvl->LoadFromFile(game.lvl_map);
	game.view = std::make_shared<View>();
	game.view->reset(FloatRect(0, 0, 640, 480));
}

void InitBonuses(GameConfig & game, BonusConfig & config, std::list<std::shared_ptr<Bonuses>> * bonuses) {
	std::vector<Object> bonus = game.lvl->GetObjects("bonus");
	for (int i = 0; i < bonus.size(); i++)
		bonuses->push_back(std::make_shared<Bonuses>(config, "Star", bonus[i].rect.left, bonus[i].rect.top, config.bonus_size.x, config.bonus_size.y));
}

void InitNpc(GameConfig & game, NPCConfig & config, std::list<std::shared_ptr<NonPlayer>> * NPCs) {
	std::vector<Object> all_obj;
	all_obj = game.lvl->GetAllObjects();
	std::string Name;
	std::string npc_check = "npc_";
	for (int i = 0; i < all_obj.size(); i++) {
		Name = "";
		if (all_obj[i].name.size() >= 4) {
			Name = all_obj[i].name;
			Name.erase(4, all_obj[i].name.size());
			if (Name == npc_check) {
				Name = all_obj[i].name;
				Name.erase(0, 4);
				config.position_npc.insert(std::pair<std::string, Vector2f>(Name, { all_obj[i].rect.left, all_obj[i].rect.top }));
				NPCs->push_back(std::make_shared<NonPlayer>(Name, config));
			}
		}
	}
}

void InitText(Information & information)
{
	information.font.loadFromFile(information.font_file);
	information.text = new Text("", information.font, information.font_size);
	information.text->setColor(Color::Black);
	information.text->setStyle(Text::Bold);
}

void InitPlayer(PlayerConfig & player_config, GameConfig & game, Hero & hero) {
	Object player_obj = game.lvl->GetObject("Player");
	hero.player = std::make_shared<Player>(player_config, *game.lvl, player_obj.rect.left, player_obj.rect.top);
}