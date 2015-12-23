#pragma once
//#include "Config.h"
//#include "Struct.h"

void InitMisionScroll(Mission & mission) {
	Image scroll_image;
	scroll_image.loadFromFile("images/mission.png");
	mission.t_scroll.loadFromImage(scroll_image);
	mission.s_scroll.setTexture(mission.t_scroll);
	mission.s_scroll.setTextureRect(IntRect(0, 0, MISSION_SCROLL_SIZE.x, MISSION_SCROLL_SIZE.y));
}

