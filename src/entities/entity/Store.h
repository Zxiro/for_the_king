#ifndef STORE_H
#define STORE_H

#include <map>
#include <string>

#include "Entity.h"
#include "../../structs/Position.h"

class Store : public Entity
{
public:
	Store(const Position &_position)
		: Entity(_position, "$")
	{
		items = {
			{"WoodenSword", 100},
			{"Hammer", 100},
			{"GiantHammer", 100},
			{"MagicWand", 100},
			{"RitualWand", 100},
			{"WoodenShield", 100},
			{"PlateArmor", 100},
			{"LeatherArmor", 100},
			{"Robe", 100},
			{"LaurelWreath", 100},
			{"HolyGrail", 100},
			{"Shoes", 100},
			{"Bracelet", 100},
			{"GodsBeard", 100},
			{"GoldenRoot", 100},
			{"TeleportScroll", 100},
			{"Tent", 100}
		};
	};

	int getItemPrice(const std::string& itemName)
	{
		return items[itemName];
	}

	void displayItems() const
	{

	}

protected:
	std::map<std::string, int> items;
};

#endif