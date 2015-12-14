// Car.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <iostream>
#include "Config.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;

void Wheels(Car & car) {
	car.s_front_wheel.setPosition(car.s_car.getPosition().x + FRONT_WHEEL_POS.x, car.s_car.getPosition().y + FRONT_WHEEL_POS.y);
	car.s_rear_wheel.setPosition(car.s_car.getPosition().x + REAR_WHEEL_POS.x, car.s_car.getPosition().y + REAR_WHEEL_POS.y);
}

void Initiation(RenderWindow & window, Car & car) {
	car.t_car.loadFromFile("\pajero.png");
	car.s_car.setTexture(car.t_car);
	car.s_car.setPosition(10, float(window.getSize().y / 2));

	car.t_wheel.loadFromFile("\wheel.png");
	car.s_front_wheel.setTexture(car.t_wheel);
	car.s_rear_wheel.setTexture(car.t_wheel);

	car.s_front_wheel.setTextureRect(WHEEL_RECT);
	car.s_rear_wheel.setTextureRect(WHEEL_RECT);

	car.radius = WHEEL_RADIUS;

	car.s_front_wheel.setOrigin(car.radius, car.radius);
	car.s_rear_wheel.setOrigin(car.radius, car.radius);

	Wheels(car);

	car.speed = 0;
	car.boost = 0.00001f;

	car.road.setSize(ROAD_SIZE);
	car.road.setPosition(0, car.s_rear_wheel.getPosition().y + car.radius);
	car.road.setFillColor(Color::Black);
}

void Speed(Car & car) {
	car.speed += car.boost;
}

float Rotate(float distantion, float radius) {
	float degree = float(float(180 * distantion) / (M_PI * radius));
	return degree;
}

void RotateWheels(Car & car, float distantion) {
	car.s_front_wheel.rotate(Rotate(distantion, car.radius));
	car.s_rear_wheel.rotate(Rotate(distantion, car.radius));
}

void MoveCar(Car & car) {
	Speed(car);
	car.s_car.move(car.speed, 0);
	Wheels(car);
	RotateWheels(car, car.speed);

}

void Boost(Car & car, RenderWindow & window) {
	if (car.s_car.getPosition().x >= window.getSize().x / 2 - car.t_car.getSize().x / 2 && car.boost > 0) {
		car.boost = car.boost * (-1);
	}
	else if ((car.s_car.getPosition().x < window.getSize().x / 2 - car.t_car.getSize().x / 2 && car.boost < 0)) {
		car.boost = car.boost * (-1);
	}
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(600, 400), "Lab8.1", sf::Style::Default, settings);
	Car car;

	Initiation(window, car);
	Clock clock;
	while (window.isOpen())
	{
		MoveCar(car);
		window.draw(car.s_car);
		window.draw(car.s_front_wheel);
		window.draw(car.s_rear_wheel);
		window.draw(car.road);
		window.display();
		window.clear(Color::White);
		Boost(car, window);
	}
}


