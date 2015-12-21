#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <cstdlib> 
#include <random> 
#include <thread>    
#include <chrono>         
#include "Config.h"

struct Snake
{
	int lenght = 4;
	int x, y;
	Texture t_fon, t_food, t_snake;
	Sprite s_fon, s_food, s_snake;

}  snake_pos[600];

struct Menu {
	Texture t_play, t_exit, t_score;
	Sprite s_play, s_exit, s_score;
	Font font;


};

void InitSnake(Snake & snake) {
	snake.t_fon.loadFromFile("fon.png");
	snake.t_food.loadFromFile("food.png");
	snake.t_snake.loadFromFile("snake.png");

	snake.s_fon.setTexture(snake.t_fon);
	snake.s_food.setTexture(snake.t_food);
	snake.s_snake.setTexture(snake.t_snake);

}
void InitMenu(Menu & menu) {

	menu.t_play.loadFromFile("play.png");
	menu.t_exit.loadFromFile("exit.png");
	menu.t_score.loadFromFile("score.png");

	menu.s_play.setTexture(menu.t_play);
	menu.s_exit.setTexture(menu.t_exit);
	menu.s_score.setTexture(menu.t_score);

	menu.s_play.setPosition(50, 30);
	menu.s_exit.setPosition(50, 150);
	menu.s_score.setPosition(200, 60);


}

void Control() {
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (dir != right) dir = left;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (dir != left) dir = right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (dir != down) dir = up;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (dir != up) dir = down;
	}
}

void MovementSnake(Snake & snake)
{ 
		for (int i = snake.lenght;i > 0;--i)
		{
			snake_pos[i].x = snake_pos[i - 1].x;
			snake_pos[i].y = snake_pos[i - 1].y;
		}

		switch (dir) {
		case down: snake_pos[0].y += 1; break;
		case left: snake_pos[0].x -= 1; break;
		case right: snake_pos[0].x += 1; break;
		case up: snake_pos[0].y -= 1; break;
		}

		if (snake_pos[0].x > N - 1) snake_pos[0].x = 0;
		if (snake_pos[0].x < 0) snake_pos[0].x = N;
		if (snake_pos[0].y > M - 1) snake_pos[0].y = 0;
		if (snake_pos[0].y < 0) snake_pos[0].y = M;

		for (int i = 1;i < snake.lenght;i++)
			if (snake_pos[0].x == snake_pos[i].x && snake_pos[0].y == snake_pos[i].y) {
				game = false;
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
	
}

bool is_empty_space(Snake & snake) {
	for (int i = 1;i < snake.lenght;i++) {
		if (snake_pos[i].x == food_position.x && snake_pos[i].y == food_position.y)
			return false;
	}
	if (is_empty_space != false)
		return true;
       
}
void NewFood(Snake & snake) {

	food_position.y = float(random_number(M));
	food_position.x = float(random_number(N));
	if (is_empty_space == false) {
		NewFood(snake);
	}

}

void EatFood(Snake & snake) {
	if ((snake_pos[0].x == food_position.x) && (snake_pos[0].y == food_position.y))
	{
		snake.lenght++;
		score++;
		NewFood(snake);
	}
}

void Timer(float & time, Snake & snake) {
	timer += time;
	if (timer > 0.1) {
		timer = 0; 
		MovementSnake(snake);
		EatFood(snake);
	}
}
void NewGame(Snake & snake) {
		game = true;
		snake.lenght = 4;
		score = 0;
		NewFood(snake);
}

void MainMenu(RenderWindow & window, Menu & menu, Snake & snake)
{
	int MenuNum = 0;
	window.clear(Color::White);

	if (IntRect(0, 0, 300, 100).contains(Mouse::getPosition(window))) MenuNum = 1;
	if (IntRect(0, 150, 300, 100).contains(Mouse::getPosition(window))) MenuNum = 2; 

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (MenuNum == 1) NewGame(snake);;
		if (MenuNum == 2) { window.close(); }

	}

	std::ostringstream score_string;
	score_string << score;

	Font font;
	font.loadFromFile("text.ttf");
	Text text("", font, 40);
	text.setColor(Color::Black);
	text.setString(score_string.str());
	text.setPosition(250, 150);

	window.draw(menu.s_play);
	window.draw(menu.s_exit);
	window.draw(menu.s_score);
	window.draw(text);
	window.display();
}

void Draw(RenderWindow & window, Snake & snake) {
	for (int i = 0; i < WINDOW_SIZE.x; i += Scale)
		for (int j = 0; j < WINDOW_SIZE.y; j += Scale)
		{
			snake.s_fon.setPosition(float(i), float(j));
			window.draw(snake.s_fon);
		}

	for (int i = 0;i < snake.lenght;i++)
	{
		snake.s_snake.setPosition(float(snake_pos[i].x*Scale), float(snake_pos[i].y*Scale));
		window.draw(snake.s_snake);
	}

	snake.s_food.setPosition(food_position.x*Scale, food_position.y*Scale);
	window.draw(snake.s_food);
}

void ExitGame(RenderWindow & window) {
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

 

int main()
{
	RenderWindow window(VideoMode(unsigned int(WINDOW_SIZE.x), unsigned int(WINDOW_SIZE.y)), "Snake");

	Snake snake;
	Clock clock;
	Menu menu;
	InitSnake(snake);
	InitMenu(menu);
	while (window.isOpen())
	{   		
		MainMenu(window, menu, snake);

		ExitGame(window);
		while (game == true) {
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
		
			ExitGame(window);

			Control();

			Timer(time, snake);
			window.clear();
			Draw(window, snake);
			window.display();
		}		
	}

	return 0;
}