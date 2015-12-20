// 7.3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <memory>
#include <iostream>

using namespace sf;

struct Config {
	std::string gear = "gear.png";
	std::string pendulum = "pendulum.png";
};

struct Gear {
	Texture texture;
	Sprite sprite;

	int rotate_side;
};

struct Pendulum {
	Texture texture;
	Sprite sprite;

	int side = 1;
	float speed = 0;
	int boost;
	bool flag = true;

	float degree = 0;
	const float MAX_DEGREE = 20;
};

void init_gear(Gear & gear, std::string name, int side, Vector2f pos) {
	Image image;
	image.loadFromFile(name);
	gear.texture.loadFromImage(image);
	gear.sprite.setTexture(gear.texture);
	gear.sprite.setOrigin(float(gear.texture.getSize().x / 2), float(gear.texture.getSize().y / 2));
	gear.rotate_side = side;
	gear.sprite.setPosition(pos);

}

void init_pendulum(Pendulum & pendulum, std::string name, Vector2f pos) {
	Image image;
	image.loadFromFile(name);
	pendulum.texture.loadFromImage(image);
	pendulum.sprite.setTexture(pendulum.texture);
	pendulum.sprite.setOrigin(float(pendulum.texture.getSize().x / 2), 0);
	pendulum.sprite.setPosition(pos);
	pendulum.sprite.setRotation(pendulum.MAX_DEGREE);
	pendulum.boost = -1;

}

void update(Gear & gear) {
	gear.sprite.rotate(3 * float(gear.rotate_side));
}

void pendulum_step(Pendulum & pendulum, Gear & gear1, Gear & gear2){
	if (pendulum.speed <= 0) {
		pendulum.speed = 0;
		pendulum.boost = pendulum.boost * (-1);
		pendulum.side = pendulum.side * (-1);
		pendulum.flag = true;
		update(gear1);
		update(gear2);

	}
	pendulum.sprite.rotate(pendulum.speed * pendulum.side);

	if (pendulum.sprite.getRotation() < 1 && pendulum.flag == true) {
		pendulum.boost = pendulum.boost * (-1);
		pendulum.flag = false;
	}

}

void drawing(RenderWindow & window, Pendulum & pendulum, Gear & gear1, Gear & gear2) 
{
	window.clear(Color::White);
	window.draw(gear1.sprite);
	window.draw(gear2.sprite);
	window.draw(pendulum.sprite);
	window.display();
}

void process(RenderWindow & window, Pendulum & pendulum, Gear & gear1, Gear & gear2){
	Clock clock;
	float time;
	while (window.isOpen())
	{
		time = float(clock.getElapsedTime().asMicroseconds());
		time = time/100000;
		pendulum.speed += time * pendulum.boost;
		pendulum_step(pendulum, gear1, gear2);
		drawing(window, pendulum, gear1, gear2);
		clock.restart();
	}
}

int main()
{
	Pendulum pendulum;
	Gear gear1;
	Gear gear2;
	Config config;
	init_gear(gear1, config.gear, 1, { 150, 150 });
	init_gear(gear2, config.gear, -1, { 340, 140 });
	init_pendulum(pendulum, config.pendulum, { 500, 100 });
	RenderWindow window(VideoMode(800, 600), "7.3");
	process(window, pendulum, gear1, gear2);
    return 0;
}

