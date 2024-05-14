#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <string>

#include "EventManager.h"
#include "UIManager.h"
#include "../entities/entity/creature/Player.h"
#include "../entities/entity/RandomEvent.h"
#include "../controller/GameStateController.h"
#include "../entities/Backpack.h"

using namespace std;

class GameManager
{
public: 
	vector<vector<string>> map;
	vector<Player> players;
	vector<Player> enemies;
	vector<RandomEvent> worldEvent;
	Backpack backpack;
	EventManager eventManager;
	UIManager uiManager;
	GameStateController gameStateController;
	//BattleManager battleManager;

protected:
};

#endif