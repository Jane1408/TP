#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>


using namespace sf;
using namespace std;


struct Files {
	string *files = new string[0];
	int size = 0;
	string path;
}typedef Files;

struct Picture {
	string name;
	Texture *texture = new Texture;
	float width;
	float height;
	Sprite *sprite = new Sprite;
	int number = 0;

}typedef Picture;


struct Configuration
{
	std::string left = "./files/left.png";
	std::string right = "./files/right.png";
	std::string zoom = "./files/zoom.png";
	std::string zoom_out = "./files/zoom_out.png";
};

struct ImageViewer {
	sf::RenderWindow window;

	Vector2u window_size;
	Vector2u size;

	View view;

	sf::Texture t_zoom;
	sf::Texture t_zoom_out;
	sf::Texture t_right;
	sf::Texture t_left;

	sf::Sprite s_zoom;
	sf::Sprite s_zoom_out;
	sf::Sprite s_right;
	sf::Sprite s_left;


	float center_x;
	float center_y;

	float increase = 1;
	float scale = 1;
	string path;

	bool is_move = false;
};