#pragma once
#include <map>
#include <string>
#include <typeindex>

#include "../exception/ItemNotEnoughException.h"
#include "../entities/item/equipment/accessory/Bracelet.h"
#include "../entities/item/equipment/accessory/Shoes.h"
#include "../entities/item/equipment/armor/LaurelWreath.h"
#include "../entities/item/equipment/armor/PlateArmor.h"
#include "../entities/item/equipment/armor/Robe.h"
#include "../entities/item/equipment/armor/WoodenShield.h"
#include "../entities/item/equipment/weapon/GiantHammer.h"
#include "../entities/item/equipment/weapon/MagicWand.h"
#include "../entities/item/equipment/weapon/RitualSword.h"
#include "../utils/MapUtil.h"
#include "../entities/item/equipment/accessory/HolyGrail.h"
#include "../entities/item/equipment/armor/LeatherArmor.h"
#include "../entities/item/equipment/weapon/Hammer.h"
#include "../entities/item/equipment/weapon/WoodenSword.h"
#include "../utils/StringUtil.h"
/*
#include "../entities/item/GodsBeard.h"
#include "../entities/item/GoldenRoot.h"
#include "../entities/item/TeleportScroll.h"
#include "../entities/item/Tent.h"
*/
class BackpackManager
{
public:
	BackpackManager()
	{
		items = {
			{typeid(WoodenSword), 10},
			{typeid(Hammer), 0},
			{typeid(GiantHammer), 0},
			{typeid(MagicWand), 0},
			{typeid(RitualSword), 0},
			{typeid(WoodenShield), 0},
			{typeid(PlateArmor), 10},
			{typeid(LeatherArmor), 0},
			{typeid(Robe), 0},
			{typeid(LaurelWreath), 0},
			{typeid(HolyGrail), 0},
			{typeid(Shoes), 0},
			{typeid(Bracelet), 0},
			/*
			{typeid(GodsBeard), 100},
			{typeid(GoldenRoot), 100},
			{typeid(TeleportScroll), 100},
			{typeid(Tent), 100}*/
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

	void addMoney(int money)
	{
		this->money += money;
	}

	void addItem(const std::string& itemName)
	{
		auto item = MapUtil<std::type_index, int>::findFirst(this->items, [&](const std::type_index& key)
			{
				return StringUtil::getName(key) == itemName;
			});
		items[item.first] += 1;
	}

	void removeItem(const std::string& itemName)
	{
		auto item = MapUtil<std::type_index, int>::findFirst(this->items, [&](const std::type_index& key)
			{
				return StringUtil::getName(key) == itemName;
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
	int money = 600;
	std::map<std::type_index, int> items;
};