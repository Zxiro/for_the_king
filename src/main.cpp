#include "Test.h"
#include "entities/entity/creature/Player.h"
#include "entities/item/equipment/weapon/WoodenSword.h"
#include "manager/GameMap.h"
#include "entities/entity/Wall.h"
#include "entities/entity/Store.h"
#include "entities/entity/Tent.h"
#include "entities/entity/RandomEvent.h"

int main()
{
    srand(static_cast<unsigned int>(time(0)));

	Player player(Position{ 1,2 }, "Player1");

	WoodenSword weapon;
	player.wearWeapon(&weapon);
	player.getPAttack();

	//Test test;
	//test.printUI();
	GameMap gameMap(140, 50);

    gameMap.addEntity(std::make_shared<Wall>(Position{ 10, 10 }), 10, 10);
    gameMap.addEntity(std::make_shared<Store>(Position{ 5, 5 }), 5, 5);
    gameMap.addEntity(std::make_shared<Player>(Position{ 1, 2 }, "Player1"), 1, 2);
    gameMap.addEntity(std::make_shared<Tent>(Position{ 7, 7 }), 7, 7);
    gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 8, 8 }, EventType::FoundMoney), 8, 8);
    gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 9, 9 }, EventType::SteppedOnMine), 9, 9);
    //gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 10, 10 }, EventType::Teleport), 10, 10);
    gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 11, 11 }, EventType::Blessed), 11, 11);
    gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 12, 12 }, EventType::Cursed), 12, 12);

    if (!gameMap.isPassable(10, 10)) {
        std::cout << "Position (10, 10) is not passable." << std::endl;
    }

    if (gameMap.isPassable(5, 5)) {
        std::cout << "Position (5, 5) is passable." << std::endl;
    }
    else {
        auto entity = gameMap.getEntity(5, 5);
        if (std::dynamic_pointer_cast<Store>(entity)) {
            std::cout << "Store at position (5, 5)." << std::endl;
        }
    }


	//KeyboardInputUI keyboardInputUI;
	//keyboardInputUI.Show();

	return 0;
}
