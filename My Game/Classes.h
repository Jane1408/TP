#pragma once
#include "stdafx.h"
#include <memory>
//#include <>
//#include <SFML/Graphics.hpp>
//#include "level.h"
//#include "view.h"

using namespace sf;
using namespace std;



class Bonuses {
public:
	std::vector<Object> obj;
	float dx, dy, x, y;
	int w, h;
	bool draw;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;
	String name, lev;
	Bonuses(BonusConfig & config, String Name, Level &lev, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0;
		draw = true;
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(config.img_bonus);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(float(w / 2), float(h / 2));
		obj = lev.GetAllObjects();
		if (name == "Star") {
			sprite->setTextureRect(IntRect(0, 0, w, h));
		}
		sprite->setPosition(x + w / 2, y + h / 2);
	}
	void _animation(float & time) {
			sprite->setRotation(sprite->getRotation() + time / 25);
	}
	void update(float time) {
		_animation(time);
	}



	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
};

//////////////////////////////////////////////////// À¿—— »√–Œ ¿////////////////////////
class Player {
public:
	std::vector<Object> obj;
	Vector2f position;
	float  dx, dy, speed;
	bool isMove;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;
	String name;
	enum { left, right, up, down, stay } state;
	int playerScore;

	Player(PlayerConfig & config, Level & lvl, float x, float y) {
		position = { x, y };
		playerScore = 0;
		state = stay;
		obj = lvl.GetAllObjects();
		speed = 0.1;
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		image.loadFromFile(config.img_player);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(float(config.size_player.x / 2), float(config.size_player.y / 2));
		sprite->setTextureRect(IntRect(0, 0, config.size_player.x, config.size_player.y));

	}

	void _control() {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) { state = left; }

			else if (Keyboard::isKeyPressed(Keyboard::Right)) { state = right; }

			else if (Keyboard::isKeyPressed(Keyboard::Up)) { state = up; }
			
			else if (Keyboard::isKeyPressed(Keyboard::Down)) { state = down; }
		}
	}

	FloatRect getRect(PlayerConfig & config) {
		return FloatRect(position.x, position.y + config.size_player.y * 0.75, config.size_player.x, config.size_player.y * 0.25);
	}

	void _checkCollisionWithMap(float Dx, float Dy, PlayerConfig & config)
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
	

	
	void update(float time, PlayerConfig & config, View & view)
	{
		_control();
		switch (state)
		{
		case right: dx = speed; dy = 0; break;
		case left:dx = -speed; dy = 0; break;
		case up: dx = 0;dy = -speed; break;
		case down: dx = 0;dy = speed;break;
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
};



class NonPlayer {
public:
	string name;
	float CurrentFrame;
	float animation_speed;
	int frame;
	Vector2f size;
	Vector2f position;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;
	NonPlayer(String Name, NPCConfig & config) {
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		frame = 0;
		animation_speed = 0.01f;
		CurrentFrame = 0;
		name = Name;
		image.loadFromFile(config.img_npc[name]);
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setTextureRect(IntRect(config.frame_pos_npc[name][frame], 0, config.size_npc[name].x, config.size_npc[name].y));
		sprite->setPosition(config.position_npc[name]);
	}

	void _animation(float time, NPCConfig & config) {
		CurrentFrame += animation_speed * time;
		if (CurrentFrame > float(config.frame_pos_npc[name].size())) {
			CurrentFrame = 0;
		}
		frame = int(CurrentFrame);
		sprite->setTextureRect(IntRect(config.frame_pos_npc[name][frame], 0, config.size_npc[name].x, config.size_npc[name].y));

	}

	void update(float time, NPCConfig & config)
	{
		_animation(time, config);

	}

	FloatRect getRect(NPCConfig & config) {
		return FloatRect(config.position_npc[name].x, config.position_npc[name].y, config.size_npc[name].x, config.size_npc[name].y);
	}
};


