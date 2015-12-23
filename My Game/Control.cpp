#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Control.h"


enum { to_right, to_left, to_up, to_down, was_right, was_left, was_up, was_down} direction;
enum { be_right, be_left, be_up, be_down } non_direction;
float CurrentFrame = 0;
float speed = 0.01;

void controlPlayer(Sprite & sprite, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down, int w, int h) {
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
		if (CurrentFrame > 8) CurrentFrame -= 8;
		sprite.setTextureRect(IntRect(w * int(CurrentFrame), 530, w, h));
		break;
	case to_left:
		CurrentFrame += speed*time;
		if (CurrentFrame > 8) CurrentFrame -= 8;
		sprite.setTextureRect(IntRect(w * int(CurrentFrame) + w, 530, -w, 100));
		break;
	case to_up:
		CurrentFrame += speed*time;
		if (CurrentFrame > 8) CurrentFrame -= 8;
		sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 430, 56, 100));
		break;
	case to_down:
		CurrentFrame += speed*time;
		if (CurrentFrame > 8) CurrentFrame -= 8;
		sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 320, 56, h));
		break;
	case was_right:
		CurrentFrame += speed*time;
		if (CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(54 * int(CurrentFrame), 207, 54, 106));
		break;
	case was_left:
		CurrentFrame += speed*time;
		if (CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(54 * int(CurrentFrame) + 54, 207, -54, 106));
		break;
	case was_up:
		CurrentFrame += speed*time;
		if (CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(62 * int(CurrentFrame), 101, 62, 106));
		break;
	case was_down:
		CurrentFrame += speed*time;
		if (CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(56 * int(CurrentFrame), 0, 56, 100));
		break;
	}
}

void AttackControlPlayer(Sprite & sprite, float & time, enum::Keyboard::Key go_left, enum::Keyboard::Key go_right, enum::Keyboard::Key go_up, enum::Keyboard::Key go_down, int w, int h) {
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
			if (CurrentFrame > 8) CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(72 * int(CurrentFrame), 875, 72, 115));
			break;
		case to_left:
			CurrentFrame += speed*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(72 * int(CurrentFrame) + 72, 875, -72, 115));
			break;
		case to_up:
			CurrentFrame += speed*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 760, 65, 110));
			break;
		case to_down:
			CurrentFrame += speed*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame), 640, 70, 120));
			break;
		case was_right:
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame), 1220, 70, 100));
			break;
		case was_left:
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(70 * int(CurrentFrame) + 70, 1220, -70, 110));
			break;
		case was_up:
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(60 * int(CurrentFrame), 1105, 60, 105));
			break;
		case was_down:
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 1000, 65, 105));
			break;
		}
}

