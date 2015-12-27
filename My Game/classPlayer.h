#pragma once
#include "Struct.h"
#include "level.h"

using namespace sf;
using namespace std;


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

	Player(PlayerConfig & config, Level & lvl, float x, float y) {
		position = { x, y };
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

	void _control();

	FloatRect getRect(PlayerConfig & config);

	void _checkCollisionWithMap(float Dx, float Dy, PlayerConfig & config);


	void update(float time, PlayerConfig & config, View & view);
};
