#pragma once
#include "Struct.h"
#include "level.h"

using namespace sf;
using namespace std;


class Player {
public:
	std::vector<Object> obj;
	Vector2f position;
	Vector2f velocity;
	Vector2f pos_for_check_collision;
	float speed;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;
	String name;
	enum { left, right, up, down, stay } state;

	Player(PlayerConfig & config, Level & lvl, float x, float y);

	void _control();

	FloatRect getRect(PlayerConfig & config);

	void _checkCollisionWithMap(Vector2f pos_for_check_collision, PlayerConfig & config);


	void update(float time, PlayerConfig & config, View & view);
};
