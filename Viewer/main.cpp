
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <windows.h>
#include <iostream>
#include <sstream>
#include "Struct.h"

using namespace sf;
using namespace std;



bool isImage(string file_name) {

	if (!strrchr(file_name.c_str(), '.')) {
		return false;
	}
	string ext_array[] = { "jpg","jpeg","png","gif","bmp" };
	string name = file_name.substr(file_name.find_last_of(".") + 1);
	for (string i : ext_array)
		if (name == i)
			return true;
	return false;
}

Files getFileList(string & old_path) {
	string path = old_path + string("*");
	Files files;
	files.path = old_path;
	unsigned long i = 0;

	WIN32_FIND_DATA file_data;
	HANDLE h_file = FindFirstFile(path.c_str(), &file_data);//поиск первого файла
	if (h_file != INVALID_HANDLE_VALUE) {//Если файл существует
		do {
			if (!(file_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)) {//если файл не папка
				files.size++;
			}

		} while (FindNextFile(h_file, &file_data));

		files.files = new string[files.size];
		i = 0;
		h_file = FindFirstFile(path.c_str(), &file_data);
		do {
			if (!(file_data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)) {
				if (isImage(file_data.cFileName)) {
					files.files[i] = file_data.cFileName;
					i++;
				}
			}

		} while (FindNextFile(h_file, &file_data));
		FindClose(h_file);
	}
	files.size = i;
	return files;
}

void BorderOfView(View & view, Picture *pic, float scale, float increase) {
	if (pic->texture->getSize().x * scale * increase  > view.getSize().x) {
		if (view.getCenter().x  + view.getSize().x / 2  > pic->texture->getSize().x / 2 * scale * increase + pic->sprite->getPosition().x) {
			view.setCenter(pic->texture->getSize().x / 2 * scale * increase + pic->sprite->getPosition().x - view.getSize().x / 2, view.getCenter().y);
	}
		else if (view.getCenter().x - view.getSize().x / 2 < pic->sprite->getPosition().x - pic->texture->getSize().x / 2 * scale * increase) {
			view.setCenter(pic->sprite->getPosition().x - pic->texture->getSize().x / 2 * scale * increase + view.getSize().x / 2, view.getCenter().y);
		}
	}
	if (pic->texture->getSize().y * scale * increase  > view.getSize().y) {
		if (view.getCenter().y + view.getSize().y / 2  > pic->texture->getSize().y / 2 * scale * increase + pic->sprite->getPosition().y) {
			view.setCenter(float(view.getCenter().x), float(pic->texture->getSize().y / 2 * scale * increase + pic->sprite->getPosition().y - view.getSize().y / 2));
		}
		else if (view.getCenter().y - view.getSize().y / 2 < pic->sprite->getPosition().y - pic->texture->getSize().y / 2 * scale * increase) {
			view.setCenter(view.getCenter().x, pic->sprite->getPosition().y - pic->texture->getSize().y / 2 * scale * increase + view.getSize().y / 2);
		}
	}
	
}


void InitiationImg(Vector2u window_size, Files files, Picture *picture) {
	Image *image = new Image();
	string path = files.path + files.files[picture->picture_number];
	image->loadFromFile(files.path + files.files[picture->picture_number]);
	picture->texture = new Texture();
	picture->texture->loadFromImage(*image);
	delete(image);
	picture->sprite = new Sprite();
	picture->sprite->setPosition(float(window_size.x / 2.0), float((window_size.y * 0.75) / 2.0));
	picture->sprite->setTexture(*(picture->texture));
	picture->sprite->setOrigin(float(picture->texture->getSize().x / 2.0), float(picture->texture->getSize().y / 2.0));
	picture->name = string(files.files[picture->picture_number]);

}

void ResizedEvent(Event & event, RenderWindow & window, Vector2u & window_size, Files & files, Picture & picture, View & view) {
	if (event.size.width < 300) {
		window_size.x = 300;
		window.setSize(window_size);
	}
	if (event.size.height < 300) {
		window_size.y = 300;
		window.setSize(window_size);
	}
	window_size = window.getSize();
	InitiationImg(window_size, files, &picture);
	view.setSize(float(window_size.x), float(window_size.y));
	view.setCenter(float(window_size.x / 2.0), float(window_size.y / 2.0));
}

void InitiationControl(Configuration & config, ImageViewer & manager) {
	manager.t_left.loadFromFile(config.left);
	manager.t_right.loadFromFile(config.right);
	manager.t_zoom.loadFromFile(config.zoom);
	manager.t_zoom_out.loadFromFile(config.zoom_out);

	manager.s_left.setTexture(manager.t_left);
	manager.s_right.setTexture(manager.t_right);
	manager.s_zoom.setTexture(manager.t_zoom);
	manager.s_zoom_out.setTexture(manager.t_zoom_out);
}

void SetViewerCenter(ImageViewer & manager) {
	manager.view.setCenter(float(manager.window_size.x / 2.0), float(manager.window_size.y / 2.0));
}

void Initiation(ImageViewer & manager) {
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	manager.window.create(VideoMode(800, 600), "ViewerManager", Style::Default, settings);
	manager.window.setVerticalSyncEnabled(true);
	manager.window_size = manager.window.getSize();

	manager.view.setSize(float(manager.window_size.x), float(manager.window_size.y));
	SetViewerCenter(manager);
	//путь
	manager.path = "";
	cout << "Enter Path: ";
	cin >> manager.path;

	manager.is_move = false;
}

void ImageScale(ImageViewer & manager, Picture * pic) {
	manager.scale = 1;
	if (pic->texture->getSize().x > manager.window_size.x) {
		manager.scale = float(manager.window_size.x) / pic->texture->getSize().x;
		pic->sprite->setScale(Vector2f(manager.scale, manager.scale));
	}
	if (pic->texture->getSize().y * manager.scale > manager.window_size.y) {
		manager.scale = float(manager.window_size.y / pic->texture->getSize().y);
		pic->sprite->setScale(Vector2f(manager.scale, manager.scale));
	}
	pic->sprite->setScale(Vector2f(manager.scale * manager.increase, manager.scale * manager.increase));
}

bool IsBigger(ImageViewer & manager, Picture * pic) {
	Vector2f ImageSize = { pic->texture->getSize().x * manager.scale * manager.increase , pic->texture->getSize().y * manager.scale * manager.increase };
	if (!(ImageSize.x > manager.view.getSize().x || ImageSize.y > manager.view.getSize().y)) {
		return false;
	}
	else {
		return true;
	}
}

void SetCentre(ImageViewer & manager, Picture * pic) {
	if (manager.is_move && manager.increase != 1 && IsBigger(manager, pic)) {
		manager.view.setCenter(manager.view.getCenter().x - (Mouse::getPosition(manager.window).x - manager.center.x), manager.view.getCenter().y - (Mouse::getPosition(manager.window).y - manager.center.y));
	}
	manager.center.x = float(Mouse::getPosition(manager.window).x);
	manager.center.y = float(Mouse::getPosition(manager.window).y);
}

void SetButtonPosition(ImageViewer & manager) {
	manager.s_right.setPosition(float(manager.view.getCenter().x + (manager.view.getSize().x / 2) - manager.t_right.getSize().x), float(manager.view.getCenter().y - manager.t_right.getSize().y / 2));
	manager.s_left.setPosition(manager.view.getCenter().x - (manager.view.getSize().x / 2), float(manager.view.getCenter().y - manager.t_left.getSize().y / 2));
	manager.s_zoom.setPosition(manager.view.getCenter().x - (manager.view.getSize().x / 2), float(manager.view.getCenter().y + (manager.view.getSize().y / 2) - manager.t_zoom.getSize().y));
	manager.s_zoom_out.setPosition(manager.view.getCenter().x - (manager.view.getSize().x / 2) + manager.t_zoom.getSize().x, float(manager.view.getCenter().y + (manager.view.getSize().y / 2) - manager.t_zoom_out.getSize().y));
}

void Draw(ImageViewer & manager, Picture & picture) {
	manager.window.setView(manager.view);
	manager.window.draw((*picture.sprite));
	manager.window.draw(manager.s_left);
	manager.window.draw(manager.s_right);
	manager.window.draw(manager.s_zoom);
	manager.window.draw(manager.s_zoom_out);
	manager.window_size = manager.window.getSize();
	manager.window.display();
	manager.window.clear(Color::White);
}

void Start(ImageViewer & manager, Files & files, Picture & picture) {
	while (manager.window.isOpen())
	{
		sf::Event event;
		while (manager.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				delete (picture.texture);
				delete[] files.files;
				manager.window.close();
			}

			if (event.type == sf::Event::Resized) {
				ResizedEvent(event, manager.window, manager.window_size, files, picture, manager.view);
			}
			Vector2i mousePos = Mouse::getPosition(manager.window);

			if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
				if (event.key.code == Mouse::Left) {
					Vector2i localPosition = Mouse::getPosition(manager.window);
					float x(float(mousePos.x));
					float y(float(mousePos.y));
					if ((FloatRect(manager.view.getCenter().x - (manager.view.getSize().x / 2), float(manager.view.getCenter().y - (manager.t_left.getSize().y / 2)), float(manager.t_left.getSize().x), float(manager.t_left.getSize().y)).intersects(FloatRect(x, y, 1, 1)))) {
						if (picture.picture_number == 0) {
							picture.picture_number = files.size;
						}
						picture.picture_number--;
						InitiationImg(manager.window_size, files, &picture);
						SetViewerCenter(manager);
						manager.increase = 1;
					}
					else if ((FloatRect(float(manager.view.getCenter().x + (manager.view.getSize().x / 2) - manager.t_right.getSize().x), float(manager.view.getCenter().y - manager.t_right.getSize().y / 2), float(manager.t_right.getSize().x), float(manager.t_right.getSize().y)).intersects(FloatRect(x, y, 1, 1)))) {
						if (picture.picture_number + 1 == files.size) {
							picture.picture_number = -1;
						}
						picture.picture_number++;
						InitiationImg(manager.window_size, files, &picture);
						manager.view.setCenter(float(manager.window_size.x / 2.0), float(manager.window_size.y / 2.0));
						manager.increase = 1;
					}
					else if ((FloatRect(0, float(manager.view.getSize().y - manager.t_zoom.getSize().y), float(manager.t_zoom.getSize().x), float(manager.t_zoom.getSize().y)).intersects(FloatRect(x, y, 1, 1)))) {
						if (manager.increase < 8) {
							manager.increase++;
						}
					}
					else if ((FloatRect(float(manager.t_zoom.getSize().x), float(manager.view.getSize().y - manager.t_zoom_out.getSize().y), float(manager.t_zoom_out.getSize().x), float(manager.t_zoom_out.getSize().y)).intersects(FloatRect(x, y, 1, 1)))) {
						if (manager.increase > 1) {
							manager.increase--;
						}

					}
					else {
						manager.is_move = true;
						manager.center.x = float(Mouse::getPosition(manager.window).x);
						manager.center.y = float(Mouse::getPosition(manager.window).y);
					}
				}
			}
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left) {
					manager.is_move = false;
				}

			if (Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				if (picture.picture_number == 0) {
					picture.picture_number = files.size;
				}
				picture.picture_number--;
				InitiationImg(manager.window_size, files, &picture);
				SetViewerCenter(manager);
				manager.increase = 1;
			}
			if (Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (picture.picture_number + 1 == files.size) {
					picture.picture_number = -1;
				}
				picture.picture_number++;
				InitiationImg(manager.window_size, files, &picture);
				SetViewerCenter(manager);
				manager.increase = 1;
			}
		}
		if (manager.increase == 1) {
			SetViewerCenter(manager);
		}

		manager.window.setTitle(picture.name + " - Lab4-5");

		ImageScale(manager, &picture);
		SetCentre(manager, &picture);
		BorderOfView(manager.view, &picture, manager.scale, manager.increase);
		SetButtonPosition(manager);
		Draw(manager, picture);
	}
}


int main() {
	Configuration config;
	ImageViewer manager;

	InitiationControl(config, manager);
	Initiation(manager);

	Files files = getFileList(manager.path);
	Picture picture;
	picture.texture->loadFromFile("./files/transparent.png");
	InitiationImg(manager.window_size, files, &picture);

	Start(manager, files, picture);
	
	}
