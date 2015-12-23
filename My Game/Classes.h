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
	float dx, dy, x, y, AFrame;
	int w, h;
	bool draw;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	String name, lev;
	Bonuses(Image &image, String Name, Level &lev, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H; name = Name;
		dx = 0; dy = 0; AFrame = 0;
		draw = true;
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(float(w / 2), float(h / 2));
		obj = lev.GetAllObjects();
		if (name == "Star") {
		sprite->setTextureRect(IntRect(0, 0, w, h));
	}
	
	}

	void update(float time) {
		if (draw == true) {
			sprite->setPosition(x + w / 2, y + h / 2);
		}

		
	}
	void Animation(float & time) {
		if (draw == true) {
			sprite->setRotation(sprite->getRotation() + time / 25);
		}

	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
};

class Entity {
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer, A;
	int w, h, health, position;
	bool life, isMove, battle;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H, int P) {
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0; position = P;
		speed = 0; health = 100; dx = 0; dy = 0; A = 0;
		life = true; isMove = false;
		texture = std::make_shared<Texture>();
		sprite = std::make_shared<Sprite>();
		texture->loadFromImage(image);
		sprite->setTexture(*texture);
		sprite->setOrigin(float(w / 2), float(h / 2));
	}

		void Animation(float time) {
		A += 0.1*time;
		if (A > 8) A -= 8;
		sprite->setTextureRect(IntRect(w * int(A), 0, w, 120));
//		sprite.move(-0.1*time, 0);
	}
};
////////////////////////////////////////////////////ÊËÀÑÑ ÈÃÐÎÊÀ////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, stay } state;
//	enum { above, below, onright, onleft } location;
	int playerScore;

	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H, int P) :Entity(image, Name, X, Y, W, H, P) {
		playerScore = 0;
		state = stay; 
		obj = lev.GetAllObjects(); 
		speed = 0.1; 
		battle = false;
		if (name == "FirePrincess") {
			sprite->setTextureRect(IntRect(0, position, w, h));
		}
	}

	void control() {
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				state = left;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				state = right;
			}

			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				state = up; 
			}

			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				state = down;
			}
		}
	}
	FloatRect getRect() {
		return FloatRect(x, y + h * 0.75, w, h * 0.25);
	}

	void checkCollisionWithMap(float Dx, float Dy)
	{

		for (int i = 0; i<obj.size(); i++)
			if (getRect().intersects(obj[i].rect))
			{
				if ((obj[i].name == "solid")  ){
					if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height - 0.75 * h;   dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; dx = 0; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0; }
				}
			}
	
	
			}
	
	
	void update(float time)
	{
		control();
		switch (state)
		{
		case right: dx = speed; dy = 0; break;
		case left:dx = -speed; dy = 0; break;
		case up: dx = 0;dy = -speed; break;
		case down: dx = 0;dy = speed;break;
		case stay: dx = 0; dy = 0;break;
		}
		x += dx*time;
		checkCollisionWithMap(dx, 0);
		y += dy*time;
		checkCollisionWithMap(0, dy);
		sprite->setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
		if (!isMove) { state = stay; }
//		setPlayerCoordinateForView(x, y);
		if (life) { setPlayerCoordinateForView(x, y); }
	}
};
/*class Enemy :public Entity {
public:

	float A;
	Enemy(Image &image, String Name, Level &lvl, float X, float Y, int W, int H, int P) :Entity(image, Name, X, Y, W, H, P) {
		A = 0;

		if (name == "enemy") {
			sprite->setTextureRect(IntRect(0, 0, w, h));
		}
	}
	void Animation(float time) {
		A += 0.005*time;
		if (A > 8) A -= 8;
		sprite->setTextureRect(IntRect(w * int(A), 0, w, h));
	}
	void update(float time)
	{

		if (name == "enemy") {
			sprite->setPosition(x + w / 2, y + h / 2);
			if (health <= 0) { life = false; }
		}
	}


};*/


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


