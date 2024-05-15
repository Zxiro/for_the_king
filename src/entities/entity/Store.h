#ifndef STORE_H
#define STORE_H

#include <map>
#include <string>

#include "Entity.h"
#include "../../exception/MoneyNotEnoughException.h"
#include "../../manager/GameManager.h"
#include "../../manager/Singleton.h"
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

	void buyItem(const std::string &itemName)
	{
		int money = Singleton<GameManager>::instance()->backpack.getMoney();
		int price = items[itemName];

		if (money < price)
			throw MoneyNotEnoughException();

		Singleton<GameManager>::instance()->backpack.setMoney(money - price);
		Singleton<GameManager>::instance()->backpack.addItem(itemName);
	}

	std::map<std::string, int> getItems() const
	{
		return items;
	}

protected:
	std::map<std::string, int> items;
};

#endif