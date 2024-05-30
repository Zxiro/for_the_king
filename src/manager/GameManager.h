#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

#include "../entities/Board.h"
#include "../entities/entity/RandomEvent.h"
// #include "../entities/item/Tent.h"

// TODO:: �a�^�X� �M �ʶ�q�ɥ�T�s�b�O�A�C
class GameManager {
public:
  GameManager() {
    players = {};
    enemies = {};
    worldEvent = {};
    map = new Board(140, 50);
  }
  int currentPlayer = 0;
  std::vector<Player> players;
  std::vector<Player> enemies;
  std::vector<RandomEvent> worldEvent;
  Board *map;
  // UIManager uiManager;
  // GameStateManager gameStateManager;
  // EventManager eventManager;
  // BattleManager battleManager;

  // bool isPositionValid(const Position& position) {
  // 	// �T�O�m�i�q�(Road) �B �b�i�ʪ�W
  // 	return map->canTeleport(position.x, position.y);
  // }

  // void teleportPlayer(Player& player, const Position& newPosition) {
  // 	if (isPositionValid(newPosition)) {
  // 		player.setPosition(newPosition);
  // 	}
  // 	else {
  // 		throw std::invalid_argument("Invalid teleport position.");
  // 	}
  // }

  // void addEntity(std::shared_ptr<Entity> entity) {
  // 	map->addEntity(entity);
  // 	if (auto tent = std::dynamic_pointer_cast<Tent>(entity)) {
  // 		tents.push_back(tent);
  // 	}
  // }

  // void updateTents() {
  // 	for (auto it = tents.begin(); it != tents.end(); ) {
  // 		auto tent = *it;
  // 		tent->incrementTurnCounter();
  // 		if (tent->shouldRemove()) {
  // 			map->removeEntity(tent->getPosition());
  // 			it = tents.erase(it);
  // 		}
  // 		else {
  // 			++it;
  // 		}
  // 	}
  // }

  // void healPlayersOnTents() {
  // 	for (auto& player : players) {
  // 		auto pos = player.getPosition();
  // 		if (auto entity = map->getEntity(pos.x, pos.y)) {
  // 			if (auto tent = std::dynamic_pointer_cast<Tent>(entity))
  // { 				int healthGain = 50; int focusGain = 5;
  // player.heal(healthGain, focusGain);
  // 			}
  // 		}
  // 	}
  // }

  // void endPlayerTurn(int playerIndex) {
  // 	// �a�^�X�Ĳ�o�b�O�v�
  // 	healPlayersOnTents();
  // 	// �s�b�O�A
  // 	updateTents();
  // }

  // void playerMove(int playerIndex) {
  // 	// �a�ʮ�Ĳ�o�b�O�ˬd
  // 	updateTents();
  // }

private:
  // std::vector<std::shared_ptr<Tent>> tents;

protected:
};

#endif