#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

#include "../entities/entity/RandomEvent.h"
#include "../entities/Board.h"

class GameManager
{
public:
	GameManager()
	{
		players = {};
		enemies = {};
		worldEvent = {};
		map = new Board(140, 50);
	}
	int currentPlayer = 0;
	std::vector<Player> players;
	std::vector<Player> enemies;
	std::vector<RandomEvent> worldEvent;
	Board* map;
	//UIManager uiManager;
	//GameStateManager gameStateManager;
	//EventManager eventManager;
	//BattleManager battleManager;

protected:
};

#endif