#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

#include "EventManager.h"
#include "UIManager.h"
#include "../entities/Backpack.h"
#include "../entities/entity/RandomEvent.h"
#include "../entities/entity/creature/Player.h"
#include "../manager/GameStateManager.h"
#include "../entities/Board.h"

class GameManager
{
public: 
	std::vector<Player> players;
	std::vector<Player> enemies;
	std::vector<RandomEvent> worldEvent;
	Board map;
	Backpack backpack;
	EventManager eventManager;
	UIManager uiManager;
	GameStateManager gameStateManager;
	//BattleManager battleManager;

protected:
};

#endif