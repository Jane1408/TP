// Clock.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "iostream"
#include <windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace sf;


struct HourHandShape
{
	ConvexShape hour = ConvexShape();
	const float hour_height = 100;
	const float hour_width = 5;

	ConvexShape minute = ConvexShape();
	const float minute_height = 150;
	const float minute_width = 5;

	ConvexShape second = ConvexShape();
	const float second_height = 200;
	const float second_width = 3;

	const int count_hours = 12;
	const int count_minutes = 60;

};

struct ClockFaceShape
{
	const float radius = 250;

	CircleShape cirlce = CircleShape(radius);
	CircleShape center = CircleShape(radius / 20);
	CircleShape big = CircleShape(radius / 40);
	CircleShape middle = CircleShape(radius / 60);
	CircleShape little = CircleShape(radius / 80);

};

ConvexShape InitHand(float height, float width) {

	sf::ConvexShape convex;
	convex.setPointCount(4);
	convex.setPoint(0, sf::Vector2f(0, 0));
	convex.setPoint(1, sf::Vector2f(-width, 0));
	convex.setPoint(2, sf::Vector2f(0, -height));
	convex.setPoint(3, sf::Vector2f(width, 0));
	convex.setOrigin(0, 0);
	return convex;
}



void ClockFace(ClockFaceShape & face, RenderWindow & window) {
	int degree = 0;
	Vector2f position;

	while (degree < 360) {
		position.x = float(face.cirlce.getPosition().x + face.radius * cos(degree* M_PI / 180));		
		position.y = float(face.cirlce.getPosition().y + face.radius * sin(degree * M_PI / 180));
		if (degree % 90 == 0) {
			face.big.setPosition(position.x, position.y);
			window.draw(face.big);
			degree++;
		}
		else if (degree % 30 == 0) {
			face.middle.setPosition(position.x, position.y);
			window.draw(face.middle);
			degree++;
		}
		else if (degree % 6 == 0) {
			face.little.setPosition(position.x, position.y);
			window.draw(face.little);
			degree++;
		}
		else {
			degree++;
		}
	}
}

void CircleOrigin(CircleShape & circle) {
	circle.setOrigin(circle.getRadius() / 2, circle.getRadius() / 2);
}

void CreateClock(HourHandShape & hand, ClockFaceShape & face, RenderWindow & window) {
	CircleOrigin(face.cirlce);
	face.cirlce.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));

	CircleOrigin(face.center);
	face.center.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));
	face.center.setFillColor(Color::Red);

	CircleOrigin(face.big);
	face.big.setFillColor(Color::Green);

	CircleOrigin(face.middle);
	face.middle.setFillColor(Color::Cyan);

	CircleOrigin(face.little);
	face.little.setFillColor(Color::Yellow);

	hand.hour = InitHand(hand.hour_height, hand.hour_width);
	hand.hour.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));
	hand.hour.setFillColor(Color::Blue);

	hand.minute = InitHand(hand.minute_height, hand.minute_width);
	hand.minute.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));
	hand.minute.setFillColor(Color::Blue);

	hand.second = InitHand(hand.second_height, hand.second_width);
	hand.second.setPosition(float(window.getSize().x / 2), float(window.getSize().y / 2));
	hand.second.setFillColor(Color::Magenta);
}

void ClockHands(HourHandShape & hand, RenderWindow & window) {
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	float rotate = ((sysTime.wHour % hand.count_hours) * (360 / hand.count_hours) + sysTime.wMinute * (float(360) / float(hand.count_hours * hand.count_minutes)) + sysTime.wSecond * (360 / float(hand.count_hours * pow(hand.count_minutes, 2))));
	hand.hour.setRotation(rotate);
	rotate = sysTime.wMinute * (360 / float(hand.count_minutes)) + sysTime.wSecond * (360 / pow(float(hand.count_minutes), 2));
	hand.minute.setRotation(rotate);
	rotate = sysTime.wSecond * 	(360 / float(hand.count_minutes));
	hand.second.setRotation(rotate);
}



int main()
{	
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(600, 600), "Clock", sf::Style::Default, settings);
	HourHandShape hand;
	ClockFaceShape face;
	CreateClock(hand, face, window);	
	while (window.isOpen()) {
		ClockHands(hand, window);
		ClockFace(face, window);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(hand.hour);
		window.draw(hand.minute);
		window.draw(hand.second);
		window.draw(face.center);
		window.display();
		window.clear(Color::White);
	}
	return 0;
}