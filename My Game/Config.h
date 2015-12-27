#pragma once
#include "classPlayer.h"
#include <memory>

struct Hero {
	std::shared_ptr<Player> player;
};
