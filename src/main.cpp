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
#include "entities/item/Godsbeard.h"
#include "entities/item/GoldenRoot.h"
#include "entities/item/TeleportScroll.h"
#include "entities/item/Tent.h"

#include "ui/MainScreen.h"

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

    EquipFactory::instance().registerClass<GodsBeard>();
    EquipFactory::instance().registerClass<GoldenRoot>();
    EquipFactory::instance().registerClass<TeleportScroll>();
    EquipFactory::instance().registerClass<Tent>();
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
	return 0;
}
