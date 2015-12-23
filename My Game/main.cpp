// My Game.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
//#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
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

void FindNpcPositions(Level & lvl, NPCConfig & config, list<std::shared_ptr<NonPlayer>> * NPCs) {
	std::vector<Object> all_obj;
	all_obj = lvl.GetAllObjects();
	string Name;
	string npc_check = "npc_";
	for (int i = 0; i < all_obj.size(); i++) {
		Name = "";
		if (all_obj[i].name.size() >= 4) {
			Name = all_obj[i].name;
			Name.erase(4, all_obj[i].name.size());
			if (Name == npc_check) {
				Name = all_obj[i].name;
				Name.erase(0, 4);
				config.position_npc.insert(pair<string, Vector2f>(Name, { all_obj[i].rect.left, all_obj[i].rect.top }));
				NPCs->push_back(std::make_shared<NonPlayer>(Name, config));

			}
		}
	}
}

int main()
{
	NPCConfig config;

	RenderWindow window(VideoMode(640, 480), "Adventure Time or Die");
	view.reset(FloatRect(0, 0, 640, 480));

	list<Bonuses*>  bonuses;
	list<Bonuses*>::iterator it;

	list<std::shared_ptr<NonPlayer>> NPCs;
	list<std::shared_ptr<NonPlayer>>::iterator character;

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setColor(Color::Black);

	Level lvl;
	lvl.LoadFromFile("level1.tmx");

	Image heroImage;
	heroImage.loadFromFile("images/firehero123.png");

	Image BonusImage;
	BonusImage.loadFromFile("images/stars.png");

	Object player = lvl.GetObject("Player");

	Object non_player_obj = lvl.GetObject("NPC");

	FindNpcPositions(lvl, config, &NPCs);

	std::vector<Object> bonus = lvl.GetObjects("bonus");

	for (int i = 0; i < bonus.size(); i++)
		bonuses.push_back(new Bonuses(BonusImage, "Star", lvl, bonus[i].rect.left, bonus[i].rect.top, BONUS_SIZE.x, BONUS_SIZE.y));
	
	Player p(heroImage, "FirePrincess", lvl, player.rect.left, player.rect.top, 50, 98, 0);
	NonPlayer bg("BubbleGum", config);

	Mission mission;
	InitMisionScroll(mission);

	bool showMissionText = true;
	bool gun = false;
	Clock clock;
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;
		
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			cout << gun << endl;
			if (gun == true) {
				gun = false;
			}
			else {
				gun = true;
			}

		}
	//	cout << gun<< "!!!!" << endl;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
			if (event.type == Event::KeyPressed)
				if ((event.key.code == Keyboard::Tab)) {

					switch (showMissionText) {

					case true: {
						ostringstream playerHealthString;
						ostringstream playerScoreString;
						playerHealthString << p.health; 
						playerScoreString << p.playerScore;
						ostringstream task;
						task << getTextMission(getCurrentMission(p.playerScore));
						text.setString("Здоровье: " + playerHealthString.str() + "\n" + task.str() + "\n" + "Собрано звезд: " + playerScoreString.str());
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
		switch (gun) {
		case true: {
			AttackControlPlayer(*p.sprite, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, p.w, p.h); break;
		}
		case false: {
			controlPlayer(*p.sprite, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, p.w, p.h); break;
		}

		}
		bg.update(time, config);
		for (it = bonuses.begin(); it != bonuses.end(); it++) { (*it)->Animation(time); }
	
//		for (ent = enemies.begin(); ent != enemies.end(); ent++) { (*ent)->update(time); }
		p.update(time);

//		for (ent = enemies.begin(); ent != enemies.end(); ent++) { (*ent)->Animation(time); }
		for (it = bonuses.begin(); it != bonuses.end(); it++)
		{
			if ((*it)->getRect().intersects(p.getRect()))
			{
				
				if ((*it)->name == "Star") {

					 (*it)->draw = false; 
					}
				}
			}

		for (it = bonuses.begin(); it != bonuses.end();)
		{
			Bonuses *b = *it;
			b->update(time);
			if (b->draw == false) {
				it = bonuses.erase(it); delete b; p.playerScore += 1;
			}
			else it++;
		}
		
		window.setView(view);
		window.clear();
		lvl.Draw(window);

		if (!showMissionText) {
			text.setPosition(view.getCenter().x + 25, view.getCenter().y - 220);
			mission.s_scroll.setPosition(view.getCenter().x + view.getSize().x / 2 - MISSION_SCROLL_SIZE.x, view.getCenter().y - view.getSize().y / 2);	
			window.draw(mission.s_scroll); window.draw(text); 
		}
		for (it = bonuses.begin(); it != bonuses.end(); it++) {
				window.draw(*(*it)->sprite); 
		}

		window.draw(*bg.sprite);
		window.draw(*p.sprite);

		window.display();
	}
	return 0;
}
