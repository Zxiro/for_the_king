#ifndef BACKPACK_H
#define BACKPACK_H

#include <map>
#include <string>

#include "../exception/ItemNotEnoughException.h"

class Backpack
{
public:
	Backpack()
		: money(600)
	{
		items = {
			{"WoodenSword", 0},
			{"Hammer", 0},
			{"GiantHammer", 0},
			{"MagicWand", 0},
			{"RitualSword", 0},
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

	void addItem(const std::string &itemName)
	{
		items[itemName] += 1;
	}

	void removeItem(const std::string &itemName)
	{
		if (items[itemName] == 0)
			throw ItemNotEnoughException();

		items[itemName] -= 1;
	}

	std::map<std::string, int> getItems() const
	{
		return items;
	}

private:
	int money;
	std::map<std::string, int> items;
};

#endif