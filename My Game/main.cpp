// My Game.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include "Struct.h"
#include "level.h"
#include "view.h"
#include "mission.h"
#include "Control.h"
#include "Classes.h"
#include "Config.h"
#include "InitiationGame.h"



using namespace sf;
using namespace std;

struct GameConfig {

	std::shared_ptr<RenderWindow> window;
	std::shared_ptr<View> view;
	std::shared_ptr<Level> lvl;
	std::string name_game = "Adventure Time or Die";
	std::string lvl_map = "level1.tmx";

};

void InitGame(shared_ptr<GameConfig> & game) {
	game->window = std::make_shared<RenderWindow>(sf::VideoMode(640, 480), game->name_game);
	game->lvl = std::make_shared<Level>();
	game->lvl->LoadFromFile(game->lvl_map);
	game->view = std::make_shared<View>();
	game->view->reset(FloatRect(0, 0, 640, 480));

}

int main()
{

	std::shared_ptr<NPCConfig> npc_config = std::make_shared<NPCConfig>();
	std::shared_ptr<PlayerConfig> player_config = std::make_shared<PlayerConfig>();
	std::shared_ptr<BonusConfig> bonus_config = std::make_shared<BonusConfig>();
	Mission mission;
	std::shared_ptr<GameConfig> game = std::make_shared<GameConfig>();
	//GameConfig game;

	InitGame(game);
	list<std::shared_ptr<Bonuses>> bonuses;
	list<std::shared_ptr<Bonuses>>::iterator bonus;

	list<std::shared_ptr<NonPlayer>> NPCs;
	list<std::shared_ptr<NonPlayer>>::iterator character;

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Black);

	Object player_obj = game->lvl->GetObject("Player");

	FindNpcPositions(*game->lvl, *npc_config, &NPCs);

	InitBonuses(*game->lvl, *bonus_config, &bonuses);
	Player p(*player_config, *game->lvl, player_obj.rect.left, player_obj.rect.top);

	NonPlayer bg("BubbleGum", *npc_config);


	InitMisionScroll(mission);

	bool showMissionText = true;

	Clock clock;
	while (game->window->isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;
		
		controlPlayer(*p.sprite, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, player_config->size_player.x, player_config->size_player.y);

		Event event;
		while (game->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game->window->close();
		
			if (event.type == Event::KeyPressed)
				if ((event.key.code == Keyboard::Tab)) {

					switch (showMissionText) {

					case true: {
						ostringstream playerHealthString;
						ostringstream playerScoreString;
						playerScoreString << p.playerScore;
						ostringstream task;
						task << getTextMission(getCurrentMission(p.playerScore));
						text.setString(task.str() + "\n" + "Собрано звезд: " + playerScoreString.str());
						showMissionText = false;
						break;
					}
					case false: {
						text.setString("");
						showMissionText = true;
						break;
					}		
				}
			}

		}
		

		for (std::shared_ptr<Bonuses> bonus : bonuses) {
			bonus->update(time); 
		}

		bg.update(time, *npc_config);
		p.update(time, *player_config, *game->view);

		//function
		for (std::shared_ptr<Bonuses> bonus : bonuses)
		{
			if (bonus->getRect().intersects(p.getRect(*player_config)))
			{
				//исправить
				if (bonus->name == "Star") {
					bonus->draw = false;
					p.playerScore += 1;
					}
				}
			}
		//*************
		//function
			auto _is_catch = [](std::shared_ptr<Bonuses> bon) {return !bon->draw;};
			bonuses.erase(remove_if(bonuses.begin(), bonuses.end(), _is_catch), bonuses.end());
		//*************

		game->window->setView(*game->view);
		game->window->clear();
		game->lvl->Draw(*game->window);

		if (!showMissionText) {
			text.setPosition(game->view->getCenter().x + 25, game->view->getCenter().y - 220);
			mission.s_scroll->setPosition(game->view->getCenter().x + game->view->getSize().x / 2 - MISSION_SCROLL_SIZE.x, game->view->getCenter().y - game->view->getSize().y / 2);
			game->window->draw(*mission.s_scroll); game->window->draw(text);
		}

		for (std::shared_ptr<Bonuses> bonus : bonuses) {
			game->window->draw(*bonus->sprite);
		}
		game->window->draw(*bg.sprite);
		game->window->draw(*p.sprite);

		game->window->display();
	}
	return 0;
}
