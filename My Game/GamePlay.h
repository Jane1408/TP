#pragma once

void GetBonus(PlayerConfig & player_config, std::list<std::shared_ptr<Bonuses>> & bonuses, Hero & hero);

void Update(PlayerConfig & player_config, NPCConfig & npc_config, std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, Hero & hero, float time, GameConfig & game);

void Draw(std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, Hero & hero, GameConfig & game);

void StartGame(std::list<std::shared_ptr<Bonuses>> & bonuses, std::list<std::shared_ptr<NonPlayer>> & NPCs, PlayerConfig & player_config, NPCConfig & npc_config, Hero & hero, GameConfig & game);