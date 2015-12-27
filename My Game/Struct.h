#pragma once
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <list>
#include <memory>
//#include "Classes.h"
//#include "classPlayer.h"
#include "level.h"

using namespace sf;

struct GameConfig {

	std::shared_ptr<RenderWindow> window;
	std::shared_ptr<View> view;
	std::shared_ptr<Level> lvl;
	std::string name_game = "Adventure Time or Die";
	std::string lvl_map = "level1.tmx";

};

struct BonusConfig  {
	std::string img_bonus = "images/stars.png";
	sf::Vector2f bonus_size = { 32, 32 };
} ;

struct NPCConfig {
	std::map <std::string, std::string> img_npc = { {"BubbleGum", "./images/booblegum.png"}

	};
	std::map <std::string, Vector2f> size_npc = { { "BubbleGum" , { 50, 100}}

	};
	std::map < std::string, std::vector<int> > frame_pos_npc = { {"BubbleGum" , {0,50,100,150,200,250}  }

	};
	std::map <std::string, Vector2f> position_npc = {

	};
	std::map <std::string, std::string> phrases_npc = {
		{ "start_BubbleGum", "Help me please!"},
	    { "finish_BubbleGum", "Thank you!"},
		{ "other_BubbleGum", "Have a good day!" }

	};
};

struct PlayerConfig {
	std::string img_player = "images/firehero123.png";
	sf::Vector2f size_player = { 50, 100 };
	int num_frame_move = 8;
	int num_frame_stay = 6;
	int other_size_one = 54;
	int other_size_two = 56;
	int other_size_three = 62;

};

struct Mission
{
	Image img_scroll;
	std::shared_ptr<Texture>  t_scroll;
	std::shared_ptr<Sprite> s_scroll;
	bool showMissionText = true;
	sf::Vector2f scroll_size = { 277, 216 };
};

struct Information
{
	Font font;
	Text *text;
	int font_size = 20;
	std::string font_file = "CyrilicOld.ttf";
};

/*struct Lists {
	std::list<std::shared_ptr<Bonuses>> bonuses;
	std::list<std::shared_ptr<Bonuses>>::iterator bonus;

	std::list<std::shared_ptr<NonPlayer>> NPCs;
	std::list<std::shared_ptr<NonPlayer>>::iterator character;

};
*/