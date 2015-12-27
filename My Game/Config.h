#pragma once
#include "classPlayer.h"
#include <memory>

struct Hero {
	std::shared_ptr<Player> player;
	int higth = 100;
	int width = 50;
	int num_frame_move = 8;
	int num_frame_stay = 6;
};
