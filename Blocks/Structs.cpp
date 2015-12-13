#include "stdafx.h"
#include "Structs.h"
#include "Config.h"

Block::Block(Vector2f size, Vector2f position, int step, int number) {
	brick_size = size;
	brick_pos = position;
	number_step = step;
	brick = new RectangleShape(brick_size);
	brick->setFillColor(Color(255, 0, 0, 255));
	brick->setPosition(brick_pos);
	transperence = 255;
	block_num = number;
}

void InitBricks(Animation & animation){
	for (int i = 0; i < NUMBER_BRICKS; i++) {
		Block NewBrick(SIZE, { START_POSITION.x - SIZE.x * i - SPACE, START_POSITION.y }, 1, i);
		animation.bricks.push_back(NewBrick);
	}
}

void DrawBricks(RenderWindow & window, Animation & animation) {
	for (Block &it : animation.bricks)
		window.draw(*it.brick);
	window.display();
	window.clear(Color::White);

}

void Delete(Animation & animation) {
	for (Block &it : animation.bricks)
		delete &it;
}

void Animation::StepOne(Block & it) {
	it.brick->move(SPEED, 0);
	it.brick_pos = it.brick->getPosition();
	if (it.brick_pos.x >= WINDOW_SIZE.x / 2) {
		it.number_step = 2;
		it.brick->setFillColor(Color(0, 255, 0, 255));
	}
}

void Animation::StepTwo(Block & it) {
	it.brick->move(0, SPEED);
	it.brick_pos = it.brick->getPosition();
	it.brick->rotate(float(720 / ((WINDOW_SIZE.y - 40) / SPEED)));
	if (it.brick_pos.y >= WINDOW_SIZE.y - 20 - SIZE.y) {
		it.brick->setRotation(0);
		it.number_step = 3;
		it.brick->setFillColor(Color(0, 0, 255, 255));
		
	}
}

void Animation::StepThree(Block & it) {
	it.brick->move(SPEED, 0);
	it.brick_pos = it.brick->getPosition();
	it.brick->setFillColor(Color(0, 0, 255, int(it.transperence)));
	if (int(it.transperence) != 0)
		it.transperence -= DELTA;
	if (it.brick_pos.x >= WINDOW_SIZE.x - 20 - SIZE.x) {
		it.number_step = 4;
		it.brick->setFillColor(Color(136, 5, 168, int(it.transperence)));
	}
}

void Animation::StepFour(Block & it) {
	it.brick->move(-SPEED, -SPEED);
	it.brick_pos = it.brick->getPosition();
	it.brick->setFillColor(Color(136, 5, 168, int(it.transperence)));
	if (int(it.transperence) != 255)
		it.transperence += DELTA;
	if (it.brick_pos.y <= WINDOW_SIZE.y / 2) {
		it.number_step = 5;
		it.brick->setFillColor(Color(0, 255, 0, 255));
	}
}

void Animation::StepFive(Block & it) {
	it.brick->move(-SPEED, 0);
	it.brick_pos = it.brick->getPosition();
	if (it.brick_pos.x >= WINDOW_SIZE.x / 4 + 50) {
		if (it.block_num % 2 == 1) {
			it.brick_size = { it.brick_size.x + ZOOM, it.brick_size.y + ZOOM };
			it.brick->setSize(it.brick_size);
		}
		else {
			it.brick_size = { it.brick_size.x - ZOOM, it.brick_size.y - ZOOM };
			it.brick->setSize(it.brick_size);
		}
	}
	else {
		if (it.block_num % 2 == 0) {
			it.brick_size = { it.brick_size.x + ZOOM, it.brick_size.y + ZOOM };
			it.brick->setSize(it.brick_size);
		}
		else {
			it.brick_size = { it.brick_size.x - ZOOM, it.brick_size.y - ZOOM };
			it.brick->setSize(it.brick_size);
		}
	} 
	if (it.brick_pos.x <= 20) {
		it.number_step = 6;
		it.brick->setFillColor(Color(0, 0, 255, 255));
	}
}

void Animation::StepSix(Block & it) {
	it.brick->move(0, -SPEED);
	it.brick_pos = it.brick->getPosition();
	if (it.brick_pos.y <= 20) {
		it.number_step = 1;
		it.brick->setFillColor(Color(255, 0, 0, 255));
	}
}