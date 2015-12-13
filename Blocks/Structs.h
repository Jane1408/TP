#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

struct Block {
	Block(Vector2f size, Vector2f position, int step, int number);
	RectangleShape * brick;
	Vector2f brick_size;
	Vector2f brick_pos;
	int number_step;
	float transperence;
	int block_num;
};

struct Animation {
	std::vector<Block> bricks;

	void StepOne(Block & it);
	void StepTwo(Block & it);
	void StepThree(Block & it);
	void StepFour(Block & it);
	void StepFive(Block & it);
	void StepSix(Block & it);
};

void InitBricks(Animation & animation);
void DrawBricks(RenderWindow & window, Animation & animation);
void Delete(Animation & animation);