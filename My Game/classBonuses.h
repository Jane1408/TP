#pragma once
#include <memory>
#include "Struct.h"


using namespace sf;
using namespace std;

class Bonuses {
public:
	float dx, dy, x, y;
	int w, h;
	bool draw;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;
	String name;
	Bonuses(BonusConfig & config, String Name, float X, float Y, int W, int H);

	void _animation(float time);

	void update(float time);

	FloatRect getRect();
};