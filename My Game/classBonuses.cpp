#include "stdafx.h"
#include "classBonuses.h"



using namespace sf;
using namespace std;


void Bonuses::_animation(float time) {
	sprite->setRotation(sprite->getRotation() + time / 25);
}

void  Bonuses::update(float time) {
	_animation(time);
}

FloatRect  Bonuses::getRect() {
	return FloatRect(x, y, w, h);
}