#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Struct.h"
#include "Config.h"
#include "Control.h"

enum { to_right, to_left, to_up, to_down, was_right, was_left, was_up, was_down} direction;
enum { be_right, be_left, be_up, be_down } non_direction;
float CurrentFrame = 0;
float speed = 0.01;

void controlPlayer(Hero & hero, PlayerConfig & config, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down) {
	if (Keyboard::isKeyPressed(go_right)) { direction = to_right; }
	else if (Keyboard::isKeyPressed(go_left)) { direction = to_left; }
	else if (Keyboard::isKeyPressed(go_up)) { direction = to_up; }
	else if (Keyboard::isKeyPressed(go_down)) { direction = to_down; }
	else if (direction == to_right) { direction = was_right; }
	else if (direction == to_left) { direction = was_left; }
	else if (direction == to_up) { direction = was_up; }
	else if (direction == to_down) { direction = was_down; }

	switch (direction) {
	case to_right:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_move) CurrentFrame -= hero.num_frame_move;
		hero.player->sprite->setTextureRect(IntRect(config.size_player.x * int(CurrentFrame), 530, config.size_player.x, config.size_player.y));
		break;
	case to_left:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_move) CurrentFrame -= hero.num_frame_move;
		hero.player->sprite->setTextureRect(IntRect(config.size_player.x * int(CurrentFrame) + config.size_player.x, 530, -config.size_player.x, config.size_player.y));
		break;
	case to_up:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_move) CurrentFrame -= hero.num_frame_move;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_two * int(CurrentFrame), 430, config.other_size_two, config.size_player.y));
		break;
	case to_down:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_move) CurrentFrame -= hero.num_frame_move;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_two * int(CurrentFrame), 320, config.other_size_two, config.size_player.y));
		break;
	case was_right:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_stay) CurrentFrame -= hero.num_frame_stay;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_one * int(CurrentFrame), 212, config.other_size_one, config.size_player.y));
		break;
	case was_left:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_stay) CurrentFrame -= hero.num_frame_stay;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_one * int(CurrentFrame) + config.other_size_one, 212, -config.other_size_one, config.size_player.y));
		break;
	case was_up:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_stay) CurrentFrame -= hero.num_frame_stay;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_three * int(CurrentFrame), 110, config.other_size_three, config.size_player.y));
		break;
	case was_down:
		CurrentFrame += speed*time;
		if (CurrentFrame > hero.num_frame_stay) CurrentFrame -= hero.num_frame_stay;
		hero.player->sprite->setTextureRect(IntRect(config.other_size_two * int(CurrentFrame), 0, config.other_size_two, config.size_player.y));
		break;
	}
}
