#ifndef STORE_H
#define STORE_H

#include <map>
#include <string>
#include <typeindex>

#include "Entity.h"
#include "../item/equipment/accessory/Bracelet.h"
#include "../item/equipment/accessory/HolyGrail.h"
#include "../item/equipment/accessory/Shoes.h"
#include "../item/equipment/armor/LaurelWreath.h"
#include "../item/equipment/armor/LeatherArmor.h"
#include "../item/equipment/armor/PlateArmor.h"
#include "../item/equipment/armor/Robe.h"
#include "../item/equipment/armor/WoodenShield.h"
#include "../item/equipment/weapon/GiantHammer.h"
#include "../item/equipment/weapon/Hammer.h"
#include "../item/equipment/weapon/MagicWand.h"
#include "../item/equipment/weapon/RitualSword.h"
#include "../item/equipment/weapon/WoodenSword.h"
#include "../entity/Tent.h"
#include "../../exception/MoneyNotEnoughException.h"
#include "../../manager/GameManager.h"
#include "../../manager/Singleton.h"
#include "../../structs/Position.h"

class Store : public Entity
{
public:
	Store() : Entity(Position{ 0, 0 }, "$") {}
	Store(const Position& _position)
		: Entity(_position, "$")
	{
		items = {
			{typeid(WoodenSword), 100},
			{typeid(Hammer), 100},
			{typeid(GiantHammer), 100},
			{typeid(MagicWand), 100},
			{typeid(RitualSword), 100},
			{typeid(WoodenShield), 100},
			{typeid(PlateArmor), 100},
			{typeid(LeatherArmor), 100},
			{typeid(Robe), 100},
			{typeid(LaurelWreath), 100},
			{typeid(HolyGrail), 100},
			{typeid(Shoes), 100},
			{typeid(Bracelet), 100},
			/*{typeid(GodsBeard), 100},
			{typeid(GoldenRoot), 100},
			{typeid(TeleportScroll), 100},*/
			{typeid(Tent), 100}
		};
	};

	void buyItem(const std::string &itemName)
	{
		int money = Singleton<GameManager>::instance().backpack->getMoney();

		auto item = MapUtil<std::type_index, int>::findFirst(this->items, [&](const std::type_index& key)
			{
				return key.name() == itemName;
			});

		int price = item.second;

		if (money < price)
			throw MoneyNotEnoughException();

		Singleton<GameManager>::instance().backpack->setMoney(money - price);
		Singleton<GameManager>::instance().backpack->addItem(itemName);
	}

	std::map<std::type_index, int> getItems() const
	{
		return items;
	}

	bool isPassable() const override {
		return true;
	}

protected:
	std::map<std::type_index, int> items;
};

#endif