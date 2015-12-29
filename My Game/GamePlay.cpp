#include "stdafx.h"
#include "Struct.h"
#include "mission.h"
#include "ClassBonuses.h"
#include "ClassNonPlayer.h"
#include "ClassPlayer.h"
#include "Config.h"
#include "Control.h"
#include "GamePlay.h"


void GetBonus(PlayerConfig & player_config, std::list<std::shared_ptr<Bonuses>> & bonuses, Hero & hero) {
	for (std::shared_ptr<Bonuses> bonus : bonuses)
	{
		if (bonus->getRect().intersects(hero.player->getRect(player_config)))
			bonus->draw = false;
	}

	auto _is_catch = [](std::shared_ptr<Bonuses> bon) {return !bon->draw;};
	bonuses.erase(remove_if(bonuses.begin(), bonuses.end(), _is_catch), bonuses.end());

}

void _updateBonus(std::list<std::shared_ptr<Bonuses>> & bonuses, float time) {
	for (std::shared_ptr<Bonuses> bonus : bonuses) {
		bonus->update(time);
	}
}

void _updateNPCs(std::list<std::shared_ptr<NonPlayer>> & NPCs, NPCConfig & npc_config, float time) {
	for (std::shared_ptr<NonPlayer> NPC : NPCs) {
		NPC->update(time, npc_config);
	}
}

void _updatePlayer(PlayerConfig & player_config, Hero & hero, float time, GameConfig & game) {
	hero.player->update(time, player_config, *game.view);
}

void Update(PlayerConfig & player_config, NPCConfig & npc_config, std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, Hero & hero, float time, GameConfig & game) {
	_updateBonus(bonuses, time);
	_updateNPCs(NPCs, npc_config, time);
	_updatePlayer(player_config, hero, time, game);
}

void _drawLevel(GameConfig & game) {
	game.lvl->DrawMap(*game.window);
}

void _drawBonus(std::list<std::shared_ptr<Bonuses>> & bonuses, GameConfig & game) {
	for (std::shared_ptr<Bonuses> bonus : bonuses) {
		game.window->draw(*bonus->sprite);
	}
}

void _drawNPCs(std::list<std::shared_ptr<NonPlayer>> & NPCs, GameConfig & game) {
	for (std::shared_ptr<NonPlayer> NPC : NPCs) {
		game.window->draw(*NPC->sprite);
	}
}

void _drawPlayer(Hero & hero, GameConfig & game) {
	game.window->draw(*hero.player->sprite);
}

void Draw(std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, Hero & hero, GameConfig & game) {
	_drawLevel(game);
	_drawBonus(bonuses, game);
	_drawNPCs(NPCs, game);
	_drawPlayer(hero, game);
}


void StartGame(std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, PlayerConfig & player_config, NPCConfig & npc_config, Hero & hero, GameConfig & game) {
	Clock clock;
	while (game.window->isOpen())
	{

		float time = game.time_config * clock.getElapsedTime().asMicroseconds();

		clock.restart();

		controlPlayer(hero, player_config, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down);

		Event event;
		while (game.window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.window->close();

			/*if (event.type == Event::KeyPressed)
			if ((event.key.code == Keyboard::Tab)) {
			//GetMission
			}*/
		}

		Update(player_config, npc_config, bonuses, NPCs, hero, time, game);
		GetBonus(player_config, bonuses, hero);

		game.window->setView(*game.view);
		game.window->clear();
		Draw(bonuses, NPCs, hero, game);

		game.window->display();
	}
}
