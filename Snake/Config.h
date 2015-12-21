#pragma once

using namespace sf;


Vector2f food_position = { 10, 10 };

int N = 30, M = 20;
int Scale = 15;

Vector2f WINDOW_SIZE = { float(Scale*N), float(Scale*M) };

int score = 0;

float timer = 0;

enum { left, right, up, down } dir;

bool game = false;

int random_number(int number) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 32700); // 
	int random_number = dist(gen) % number;
	return random_number;
}
