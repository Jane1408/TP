
#include "stdafx.h"
#include "classNonPlayer.h"
#include <memory>
#include "Struct.h"

using namespace sf;
using namespace std;

NonPlayer::NonPlayer(String Name, NPCConfig & config) {
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

void NonPlayer::_animation(float time, NPCConfig & config) {
	CurrentFrame += animation_speed * time;
	if (CurrentFrame > float(config.frame_pos_npc[name].size())) {
		CurrentFrame = 0;
	}
	frame = int(CurrentFrame);
	sprite->setTextureRect(IntRect(config.frame_pos_npc[name][frame], 0, config.size_npc[name].x, config.size_npc[name].y));

}

void NonPlayer::update(float time, NPCConfig & config)
{
	_animation(time, config);

}

FloatRect NonPlayer::getRect(NPCConfig & config) {
	return FloatRect(config.position_npc[name].x, config.position_npc[name].y, config.size_npc[name].x, config.size_npc[name].y);
}