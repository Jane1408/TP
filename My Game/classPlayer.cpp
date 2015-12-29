#include "stdafx.h"
#include "classPlayer.h"
#include <memory>
#include "view.h"
#include "Struct.h"

using namespace sf;
using namespace std;

Player::Player(PlayerConfig & config, Level & lvl, float x, float y) {
	position = { x, y };
	state = stay;
	obj = lvl.GetAllObjects();
	speed = 0.1f;
	texture = std::make_shared<Texture>();
	sprite = std::make_shared<Sprite>();
	image.loadFromFile(config.img_player);
	texture->loadFromImage(image);
	sprite->setTexture(*texture);
	sprite->setOrigin(float(config.size_player.x / 2), float(config.size_player.y / 2));
	sprite->setTextureRect(IntRect(0, 0, float(config.size_player.x), float(config.size_player.y)));

}

void Player::_control() {
	if (Keyboard::isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			state = left;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			state = right;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			state = up;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			state = down;
		}
		else
		{
			state = stay;
		}
	}
	
}

FloatRect Player::getRect(PlayerConfig & config) {
	return FloatRect(position.x, position.y + config.size_player.y * 0.75f, config.size_player.x, config.size_player.y * 0.25);
}

void Player::_checkCollisionWithMap(Vector2f pos_for_check_collision, PlayerConfig & config)
{
	for (int i = 0; i < int(obj.size()); i++)
		if (getRect(config).intersects(obj[i].rect))
		{
			if ((obj[i].name == "solid")) {
				if (pos_for_check_collision.y > 0)
				{
					position.y = obj[i].rect.top - config.size_player.y;  velocity.y = 0;
				}
				if (pos_for_check_collision.y < 0)
				{
					position.y = obj[i].rect.top + obj[i].rect.height - 0.75f * config.size_player.y;   velocity.y = 0;
				}
				if (pos_for_check_collision.x > 0)
				{
					position.x = obj[i].rect.left - config.size_player.x; velocity.x = 0;
				}
				if (pos_for_check_collision.x < 0)
				{
					position.x = obj[i].rect.left + obj[i].rect.width; velocity.x = 0;
				}
			}
		}
}

void Player::update(float time, PlayerConfig & config, View & view)
{
	_control();
	switch (state)
	{
	case right: velocity.x = speed; velocity.y = 0; break;
	case left: velocity.x = -speed; velocity.y = 0; break;
	case up: velocity.x = 0; velocity.y = -speed; break;
	case down: velocity.x = 0; velocity.y = speed; break;
	case stay: velocity.x = 0; velocity.y = 0;break;
	}	
	position.y += velocity.y*time;
	position.x += velocity.x*time;
	pos_for_check_collision = { velocity.x , velocity.y };
	_checkCollisionWithMap(pos_for_check_collision, config);
	sprite->setPosition(position.x + config.size_player.x / 2, position.y + config.size_player.y / 2);
	setPlayerCoordinateForView(position.x, position.y, view);

}