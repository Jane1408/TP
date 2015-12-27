#pragma once

void InitMisionScroll(Mission & mission);

void InitGame(GameConfig & game);

void InitBonuses(GameConfig & game, BonusConfig & config, std::list<std::shared_ptr<Bonuses>> * bonuses);

void InitNpc(GameConfig & game, NPCConfig & config, std::list<std::shared_ptr<NonPlayer>> * NPCs);

void InitText(Information & information);

void InitPlayer(PlayerConfig & player_config, GameConfig & game, Hero & hero);
