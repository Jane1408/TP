#pragma once

using namespace sf;

static const int WHEEL_RADIUS = 19;

static const Vector2f FRONT_WHEEL_POS = { 195, 90 };

static const Vector2f REAR_WHEEL_POS = { 62, 90 };

static const Vector2f ROAD_SIZE = { 1600, 100 };

static const IntRect WHEEL_RECT = { 0, 0, 38, 38 };

struct Car
{
	Car() {}
	Texture t_car;
	Sprite s_car;

	Texture t_wheel;
	Sprite s_front_wheel;
	Sprite s_rear_wheel;

	float radius;
	float speed;
	float boost;

	RectangleShape road;
};