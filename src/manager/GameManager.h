#pragma once
#include <vector>
#include <string>
#include "EventManager.h"
#include "UIManager.h"
#include "../entities/backpack/Backpack.h"
#include "../entities/entity/creature/Player.h"
#include "../entities/entity/RandomEvent.h"
#include "../controller/GameStateController.h"

using namespace std;

class GameManager {
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
};