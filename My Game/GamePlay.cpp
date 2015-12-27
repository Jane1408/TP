#include "stdafx.h"
#include "Struct.h"
#include "mission.h"
#include "ClassBonuses.h"
#include "ClassNonPlayer.h"
#include "ClassPlayer.h"
#include "Config.h"
#include "Control.h"
#include "GamePlay.h"


void GetBonus(PlayerConfig & player_config, std::list<std::shared_ptr<Bonuses>> * bonuses, Hero & hero) {
	for (std::shared_ptr<Bonuses> bonus : *bonuses)
	{
		if (bonus->getRect().intersects(hero.player->getRect(player_config)))
			bonus->draw = false;
	}

	auto _is_catch = [](std::shared_ptr<Bonuses> bon) {return !bon->draw;};
	bonuses->erase(remove_if(bonuses->begin(), bonuses->end(), _is_catch), bonuses->end());

}

void Update(PlayerConfig & player_config, NPCConfig & npc_config, std::list<std::shared_ptr<Bonuses>> * bonuses, std::list<std::shared_ptr<NonPlayer>> * NPCs, Hero & hero, float time, GameConfig & game) {
	for (std::shared_ptr<Bonuses> bonus : *bonuses) {
		bonus->update(time);
	}
	for (std::shared_ptr<NonPlayer> NPC : *NPCs) {
		NPC->update(time, npc_config);
	}
	hero.player->update(time, player_config, *game.view);
}

void Draw(std::list<std::shared_ptr<Bonuses>> * bonuses, std::list<std::shared_ptr<NonPlayer>> * NPCs, Hero & hero, GameConfig & game) {
	game.lvl->DrawMap(*game.window);
	for (std::shared_ptr<Bonuses> bonus : *bonuses) {
		game.window->draw(*bonus->sprite);
	}

	for (std::shared_ptr<NonPlayer> NPC : *NPCs) {
		game.window->draw(*NPC->sprite);
	}
	game.window->draw(*hero.player->sprite);
}


void StarGame(std::list<std::shared_ptr<Bonuses>> * bonuses, std::list<std::shared_ptr<NonPlayer>> * NPCs, PlayerConfig & player_config, NPCConfig & npc_config, Hero & hero, GameConfig & game) {
	Clock clock;
	while (game.window->isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 800;

		controlPlayer(*hero.player->sprite, time, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down, player_config.size_player.x, player_config.size_player.y);

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



/*
void GenerateMission() {

}
void GetMission(Mission & mission, Information & information) {
	switch (mission.showMissionText) {
	case true: {
		std::ostringstream task;
		task << getTextMission(getCurrentMission(p.playerScore));
		information.text->setString(task.str());
		mission.showMissionText = false;
		break;
	}
	case false: {
		information.text->setString("");
		mission.showMissionText = true;
		break;
	}
	}

}

void DrawMission() {
	if (!showMissionText) {
		information->text->setPosition(game->view->getCenter().x + 25, game->view->getCenter().y - 220);
		mission->s_scroll->setPosition(game->view->getCenter().x + game->view->getSize().x / 2 - MISSION_SCROLL_SIZE.x, game->view->getCenter().y - game->view->getSize().y / 2);
		game->window->draw(*mission->s_scroll); game->window->draw(*information->text);
	}

}

*/