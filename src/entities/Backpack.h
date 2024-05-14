#ifndef BACKPACK_H
#define BACKPACK_H

#include <map>
#include <string>

#include "../item/item.h"

class Backpack {
public:
	Backpack()
		: money(600)
	{
		items = {
			{"WoodenSword", 0},
			{"Hammer", 0},
			{"GiantHammer", 0},
			{"MagicWand", 0},
			{"RitualWand", 0},
			{"WoodenShield", 0},
			{"PlateArmor", 0},
			{"LeatherArmor", 0},
			{"Robe", 0},
			{"LaurelWreath", 0},
			{"HolyGrail", 0},
			{"Shoes", 0},
			{"Bracelet", 0},
			{"GodsBeard", 0},
			{"GoldenRoot", 0},
			{"TeleportScroll", 0},
			{"Tent", 0}
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

	void addItem(const std::string& itemName)
	{
		items[itemName] += 1;
	}

	void removeItem(const std::string& itemName)
	{
		items[itemName] -= 1;
	}

	int getItemCount(const std::string& itemName)
	{
		return items[itemName];
	}

	void displayItems() const
	{

	}

private:
	int money;
	std::map<std::string, int> items;
};

#endif