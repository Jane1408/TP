// Blocks.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Structs.h"
#include "Config.h"
#include <memory>
#include <iostream>


int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(unsigned int(WINDOW_SIZE.x), unsigned int(WINDOW_SIZE.y)), "Lab7.2", sf::Style::Default, settings);
	std::shared_ptr<Animation> animation = std::make_shared<Animation>();
	InitBricks(*animation);
	while (window.isOpen())
	{
		for (Block &it : animation->bricks) {
			switch (it.number_step) {
			case 1: animation->StepOne(it); break;
			case 2: animation->StepTwo(it); break;
			case 3: animation->StepThree(it); break;
			case 4: animation->StepFour(it); break;
			case 5: animation->StepFive(it); break;
			case 6: animation->StepSix(it); break;
			}
		}
		DrawBricks(window, *animation);
	}
	Delete(*animation);
}

