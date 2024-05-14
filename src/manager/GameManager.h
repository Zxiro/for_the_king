#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>

#include "EventManager.h"
#include "UIManager.h"
#include "../entities/Backpack.h"
#include "../entities/entity/RandomEvent.h"
#include "../entities/entity/creature/Player.h"
#include "../manager/GameStateManager.h"

class GameManager
{
public: 
	std::vector<std::vector<std::string>> map;
	std::vector<Player> players;
	std::vector<Player> enemies;
	std::vector<RandomEvent> worldEvent;
	Backpack backpack;
	EventManager eventManager;
	UIManager uiManager;
	GameStateManager gameStateManager;
	//BattleManager battleManager;

protected:
};

#endif