#include "Test.h"
#include "factory/EquipFactory.h"
#include "entities/item/equipment/accessory/Bracelet.h"
#include "entities/item/equipment/accessory/HolyGrail.h"
#include "entities/item/equipment/accessory/Shoes.h"
#include "entities/item/equipment/armor/LaurelWreath.h"
#include "entities/item/equipment/armor/LeatherArmor.h"
#include "entities/item/equipment/armor/PlateArmor.h"
#include "entities/item/equipment/armor/Robe.h"
#include "entities/item/equipment/armor/WoodenShield.h"
#include "entities/item/equipment/weapon/GiantHammer.h"
#include "entities/item/equipment/weapon/Hammer.h"
#include "entities/item/equipment/weapon/MagicWand.h"
#include "entities/item/equipment/weapon/RitualSword.h"
#include "entities/item/equipment/weapon/WoodenSword.h"
#include "entities/entity/Tent.h"


#include "ui/MainScreen.h"
#include "manager/Singleton.h"
#include <windows.h>

void registerInstance()
{
    EquipFactory::instance().registerClass<Bracelet>();
    EquipFactory::instance().registerClass<HolyGrail>();
    EquipFactory::instance().registerClass<Shoes>();
    EquipFactory::instance().registerClass<LaurelWreath>();
    EquipFactory::instance().registerClass<LeatherArmor>();
    EquipFactory::instance().registerClass<PlateArmor>();
    EquipFactory::instance().registerClass<Robe>();
    EquipFactory::instance().registerClass<WoodenShield>();
    EquipFactory::instance().registerClass<GiantHammer>();
    EquipFactory::instance().registerClass<Hammer>();
    EquipFactory::instance().registerClass<MagicWand>();
    EquipFactory::instance().registerClass<RitualSword>();
    EquipFactory::instance().registerClass<WoodenSword>();
}

void initialPlayers() {
    for (int index = 0; index < 3; ++index) {
        Player player(Position{ index + 1, 2 }, "Player" + std::to_string(index + 1));
        // Sleep(1000); 防止資料重疊
        //Hammer* hammer = new Hammer();
        //player.wearWeapon(hammer);
        //
        //PlateArmor* plateArmor = new PlateArmor();
        //player.wearArmor(plateArmor);
        //
        //HolyGrail* holyGrail = new HolyGrail();
        //player.wearAccessory(holyGrail);

        Singleton<GameManager>::instance().players.push_back(player);
    }
}

int main()
{
    registerInstance();
    initialPlayers();

    MainScreen mainScreen;
    mainScreen.printUI();
    // auto test = Singleton<GameManager>::instance().players;
    //工廠模式 use type create instance
    //Equipment* equip = EquipFactory::instance().createInstance(typeid(Hammer));

    //int money = Singleton<GameManager>::instance().backpack->getMoney();
    //std::cout << money << std::endl;

    //srand(static_cast<unsigned int>(time(0)));
    //
	//Player player(Position{ 1,2 }, "Player1");
    //
	//WoodenSword weapon;
	//player.wearWeapon(&weapon);
	//player.getPAttack();

	//Test test;
	//test.printUI();
	//GameMap gameMap(140, 50);
    //
    //gameMap.addEntity(std::make_shared<Wall>(Position{ 10, 10 }), 10, 10);
    //gameMap.addEntity(std::make_shared<Store>(Position{ 5, 5 }), 5, 5);
    //gameMap.addEntity(std::make_shared<Player>(Position{ 1, 2 }, "Player1"), 1, 2);
    //gameMap.addEntity(std::make_shared<Tent>(Position{ 7, 7 }), 7, 7);
    //gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 8, 8 }, EventType::FoundMoney), 8, 8);
    //gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 9, 9 }, EventType::SteppedOnMine), 9, 9);
    ////gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 10, 10 }, EventType::Teleport), 10, 10);
    //gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 11, 11 }, EventType::Blessed), 11, 11);
    //gameMap.addEntity(std::make_shared<RandomEvent>(Position{ 12, 12 }, EventType::Cursed), 12, 12);
    //
    //if (!gameMap.isPassable(10, 10)) {
    //    std::cout << "Position (10, 10) is not passable." << std::endl;
    //}
    //
    //if (gameMap.isPassable(5, 5)) {
    //    std::cout << "Position (5, 5) is passable." << std::endl;
    //}
    //else {
    //    auto entity = gameMap.getEntity(5, 5);
    //    if (std::dynamic_pointer_cast<Store>(entity)) {
    //        std::cout << "Store at position (5, 5)." << std::endl;
    //    }
    //}
    //
    //
	////KeyboardInputUI keyboardInputUI;
	////keyboardInputUI.Show();
    //
	return 0;
}
