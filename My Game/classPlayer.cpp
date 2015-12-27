#include "stdafx.h"
#include "classPlayer.h"
#include <memory>
#include "view.h"
#include "Struct.h"

using namespace sf;
using namespace std;


void Player::_control() {
	if (Keyboard::isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Left)) { state = left; }

		else if (Keyboard::isKeyPressed(Keyboard::Right)) { state = right; }

		else if (Keyboard::isKeyPressed(Keyboard::Up)) { state = up; }

		else if (Keyboard::isKeyPressed(Keyboard::Down)) { state = down; }
		
		else { state = stay; }
	}
	
}

FloatRect Player::getRect(PlayerConfig & config) {
	return FloatRect(position.x, position.y + config.size_player.y * 0.75, config.size_player.x, config.size_player.y * 0.25);
}

void Player::_checkCollisionWithMap(float Dx, float Dy, PlayerConfig & config)
{
	for (int i = 0; i < obj.size(); i++)
		if (getRect(config).intersects(obj[i].rect))
		{
			if ((obj[i].name == "solid")) {
				if (Dy > 0) { position.y = obj[i].rect.top - config.size_player.y;  dy = 0; }
				if (Dy < 0) { position.y = obj[i].rect.top + obj[i].rect.height - 0.75 * config.size_player.y;   dy = 0; }
				if (Dx > 0) { position.x = obj[i].rect.left - config.size_player.x; dx = 0; }
				if (Dx < 0) { position.x = obj[i].rect.left + obj[i].rect.width; dx = 0; }
			}
		}
}

void Player::update(float time, PlayerConfig & config, View & view)
{
	_control();
	switch (state)
	{
	case right: dx = speed; dy = 0; break;
	case left:dx = -speed; dy = 0; break;
	case up: dx = 0;dy = -speed; break;
	case down: dx = 0;dy = speed; break;
	case stay: dx = 0; dy = 0;break;
	}
	position.x += dx*time;
	_checkCollisionWithMap(dx, 0, config);
	position.y += dy*time;
	_checkCollisionWithMap(0, dy, config);
	sprite->setPosition(position.x + config.size_player.x / 2, position.y + config.size_player.y / 2);
	if (!isMove) { state = stay; }
	setPlayerCoordinateForView(position.x, position.y, view);

}