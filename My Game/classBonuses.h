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
	Bonuses(BonusConfig & config, String Name, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0;
		draw = true;
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(config.img_bonus);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(float(w / 2), float(h / 2));
		sprite->setTextureRect(IntRect(0, 0, w, h));
		sprite->setPosition(x + w / 2, y + h / 2);
	}
	void _animation(float time);
	void update(float time);

	FloatRect getRect();
};