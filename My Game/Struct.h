#pragma once
//#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

using namespace sf;

struct NPCConfig {
	std::map <std::string, std::string> img_npc = { {"BubbleGum", "./images/booblegum.png"}

	};
	std::map <std::string, Vector2f> size_npc = {{ "BubbleGum" , { 50, 100}}

	};
	std::map < std::string, std::vector<int> > frame_pos_npc = { { "BubbleGum" , {0,50,100,150,200,250}  }

	};
	std::map <std::string, Vector2f> position_npc = {

	};
};


