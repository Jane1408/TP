#pragma once
#include "Struct.h"
#include "level.h"

using namespace sf;
using namespace std;

class NonPlayer {
public:
	std::string name;
	float CurrentFrame;
	float animation_speed;
	int frame;
	Vector2f size;
	Vector2f position;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Sprite> sprite;
	Image image;

	NonPlayer(String Name, NPCConfig & config);

	void _animation(float time, NPCConfig & config);

	void update(float time, NPCConfig & config);

	FloatRect getRect(NPCConfig & config);
};