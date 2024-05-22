#ifndef BACKPACK_H
#define BACKPACK_H

#include <map>
#include <string>
#include <typeindex>

#include "../exception/ItemNotEnoughException.h"
#include "entity/Tent.h"
#include "item/equipment/accessory/Bracelet.h"
#include "item/equipment/accessory/Shoes.h"
#include "item/equipment/armor/LaurelWreath.h"
#include "item/equipment/armor/PlateArmor.h"
#include "item/equipment/armor/Robe.h"
#include "item/equipment/armor/WoodenShield.h"
#include "item/equipment/weapon/GiantHammer.h"
#include "item/equipment/weapon/MagicWand.h"
#include "item/equipment/weapon/RitualSword.h"
#include "../utils/MapUtil.h"

class Backpack
{
public:
	Backpack()
		: money(600)
	{
		items = {
			{typeid(WoodenSword), 2},
			{typeid(Hammer), 0},
			{typeid(GiantHammer), 0},
			{typeid(MagicWand), 0},
			{typeid(RitualSword), 0},
			{typeid(WoodenShield), 0},
			{typeid(PlateArmor), 0},
			{typeid(LeatherArmor), 2},
			{typeid(Robe), 0},
			{typeid(LaurelWreath), 0},
			{typeid(HolyGrail), 0},
			{typeid(Shoes), 0},
			{typeid(Bracelet), 0},
			/*{typeid(GodsBeard), 100},
			{typeid(GoldenRoot), 100},
			{typeid(TeleportScroll), 100},*/
			{typeid(Tent), 0}
		};
	};

	int getMoney() const
	{
		return money;
	}

	void setMoney(int _money)
	{
		money = _money;
	}

	void addItem(const std::string &itemName)
	{
		auto item = MapUtil<std::type_index, int>::findFirst(this->items, [&](const std::type_index& key)
			{
				return key.name() == itemName;
			});
		items[item.first] += 1;
	}

	void removeItem(const std::string &itemName)
	{
		auto item = MapUtil<std::type_index, int>::findFirst(this->items, [&](const std::type_index& key)
			{
				return key.name() == itemName;
			});
		if (item.second == 0)
			throw ItemNotEnoughException();

		items[item.first] -= 1;
	}

	std::map<std::type_index, int> getItems() const
	{
		return items;
	}

private:
	int money;
	std::map<std::type_index, int> items;
};

#endif