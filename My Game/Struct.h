#pragma once
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
//#include <list>
#include <memory>
//#include "Classes.h"
//#include "level.h"

using namespace sf;



struct BonusConfig {
	std::string img_bonus = "images/stars.png";
};

struct NPCConfig {
	std::map <std::string, std::string> img_npc = { {"BubbleGum", "./images/booblegum.png"}

	};
	std::map <std::string, Vector2f> size_npc = { { "BubbleGum" , { 50, 100}}

	};
	std::map < std::string, std::vector<int> > frame_pos_npc = { { "BubbleGum" , {0,50,100,150,200,250}  }

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
	sf::Vector2f size_player = { 50, 98 };
};

struct Mission
{
	std::shared_ptr<Texture>  t_scroll;
	std::shared_ptr<Sprite> s_scroll;

};
