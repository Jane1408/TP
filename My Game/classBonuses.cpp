#include "stdafx.h"
#include "classBonuses.h"



using namespace sf;
using namespace std;

Bonuses::Bonuses(BonusConfig & config, String Name, float X, float Y, int W, int H) {
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

void Bonuses::_animation(float time) {
	sprite->setRotation(sprite->getRotation() + time / 25);
}

void  Bonuses::update(float time) {
	_animation(time);
}

FloatRect  Bonuses::getRect() {
	return FloatRect(x, y, w, h);
}