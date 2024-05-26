#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

#include "../entities/entity/RandomEvent.h"
#include "../entities/Board.h"
#include "../entities/entity/creature/Player.h"
#include "../entities/item/Tent.h"
//TODO:: 玩家回合結束 和 移動階段時正確更新帳篷的狀態。
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
	bool isPositionValid(const Position& position) {
		// 確保位置可通行(Road) 且 不在可互動的物件上
		return map->canTeleport(position.x, position.y);
	}

	void teleportPlayer(Player& player, const Position& newPosition) {
		if (isPositionValid(newPosition)) {
			player.setPosition(newPosition);
		}
		else {
			throw std::invalid_argument("Invalid teleport position.");
		}
	}

	void addEntity(std::shared_ptr<Entity> entity) {
		map->addEntity(entity);
		if (auto tent = std::dynamic_pointer_cast<Tent>(entity)) {
			tents.push_back(tent);
		}
	}

	void updateTents() {
		for (auto it = tents.begin(); it != tents.end(); ) {
			auto tent = *it;
			tent->incrementTurnCounter();
			if (tent->shouldRemove()) {
				map->removeEntity(tent->getPosition());
				it = tents.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void healPlayersOnTents() {
		for (auto& player : players) {
			auto pos = player.getPosition();
			if (auto entity = map->getEntity(pos.x, pos.y)) {
				if (auto tent = std::dynamic_pointer_cast<Tent>(entity)) {
					tent->healPlayer(player);
				}
			}
		}
	}

	void endPlayerTurn(int playerIndex) {
		// 玩家回合結束時觸發帳篷治療
		healPlayersOnTents();
		// 更新帳篷狀態
		updateTents();
	}

	void playerMove(int playerIndex) {
		// 玩家移動時觸發帳篷移除檢查
		updateTents();
	}

private:
	std::vector<std::shared_ptr<Tent>> tents;

protected:
};

#endif