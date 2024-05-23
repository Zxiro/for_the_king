#ifndef BAGMODAL_H
#define BAGMODAL_H

#include "../../entities/entity/creature/Player.h";
#include "../../manager/BackpackManager.h"
#include "../../manager/GameManager.h"


using namespace std;
using namespace ftxui;

class BagModal
{
private:
	int chooseBagPlayerIndex;
	int chooseBagItemIndex;
	std::vector<Player> players;
	int money;
	map<type_index, int> backpack_items;
	vector<std::string> ui_items;
	function<void()> onRefresh;
	void wearEquipment()
	{
		int typeIndex = chooseBagItemIndex / 3;
		int playerIndex = chooseBagItemIndex % 3;
		bool isUse = false;

		auto it = MapUtil<type_index, int>::findFirst(backpack_items, [&](type_index type) {return  StringUtil::getName(type) == ui_items[typeIndex]; });
		
		std::shared_ptr<Equipment> item = EquipFactory::instance().createInstance(it.first);
		shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(item);
		shared_ptr<Armor> armor = std::dynamic_pointer_cast<Armor>(item);
		shared_ptr<Accessory> accessory= std::dynamic_pointer_cast<Accessory>(item);
		shared_ptr<Item> useItem = std::dynamic_pointer_cast<Item>(item);

		if(weapon != nullptr && !this->players[playerIndex].getWeapon())
		{
			Singleton<GameManager>::instance().players[playerIndex].wearWeapon(weapon);
		}
		else if(armor != nullptr && !this->players[playerIndex].getArmor())
		{	
			Singleton<GameManager>::instance().players[playerIndex].wearArmor(armor);
		}
		else if(accessory != nullptr && !this->players[playerIndex].getAccessory())
		{
			Singleton<GameManager>::instance().players[playerIndex].wearAccessory(accessory);
		} else
		{
			//TODO: use item;
		}

		if(isUse)
		{
			Singleton<BackpackManager>::instance().removeItem(item->getName());
		}
	}
	void takeOffEquipment()
	{
		vector<Player> players = Singleton<GameManager>::instance().players;
		// 卸下裝備
		int typeIndex = chooseBagPlayerIndex % 3;
		int playerIndex = chooseBagPlayerIndex / 3;
		if (typeIndex == 0) { // weapon
			if (players[playerIndex].getWeapon()) {
				Singleton<GameManager>::instance().players[playerIndex].removeWeapon();
			}
		}
		else if (typeIndex == 1) { // armor
			if (players[playerIndex].getArmor()) {
				Singleton<GameManager>::instance().players[playerIndex].removeArmor();
			}
		}
		else if (typeIndex == 2) { // accessory
			if (players[playerIndex].getAccessory()) {
				Singleton<GameManager>::instance().players[playerIndex].removeAccessory();
			}
		}
	}
	void refreshUI()
	{
		this->money = Singleton<BackpackManager>::instance().getMoney();
		this->backpack_items = Singleton<BackpackManager>::instance().getItems();
 		this->players = Singleton<GameManager>::instance().players;

		this->onRefresh();
	}

public:
	BagModal(function<void()> onRefresh) {
		chooseBagPlayerIndex = 0;
		chooseBagItemIndex = 0;
		this->onRefresh = onRefresh;
	}

	Component modalUI(std::function<void()> hide_modal) {
		auto bagComponent = Button("X", hide_modal);

		bagComponent |= Renderer([&](Element closeButton) {
			refreshUI();
			this->ui_items.clear();

			// 玩家資訊
			Elements playerColumn;
			int k = 0;
			for (auto& playerInfo : players)
			{
				string player_weapon = !playerInfo.getWeapon() ? "" : playerInfo.getWeapon()->getName();
				string player_armor = !playerInfo.getArmor() ? "" : playerInfo.getArmor()->getName();
				string player_accessory = !playerInfo.getAccessory() ? "" : playerInfo.getAccessory()->getName();

				auto WeaponStyle = (chooseBagPlayerIndex == (k * 3) + 0) ? bgcolor(Color::Red) : bgcolor(Color::GrayDark);
				auto ArmorStyle = (chooseBagPlayerIndex == (k * 3) + 1) ? bgcolor(Color::Red) : bgcolor(Color::GrayDark);
				auto AccessoryStyle = (chooseBagPlayerIndex == (k * 3) + 2) ? bgcolor(Color::Red) : bgcolor(Color::GrayDark);

				playerColumn.push_back(
					vbox({
						vbox({
						  text("Name: " + playerInfo.getDisplay()),
						  separator()
						}),
						hbox({
							vbox({
								text("Weapon"),
								text(player_weapon),
								text(!playerInfo.getWeapon() ? "Not Equip" : "Take off") | WeaponStyle | size(WIDTH, EQUAL, 8)
							}) | flex,
							vbox({
								text("Armor"),
								text(player_armor),
								text(!playerInfo.getArmor() ? "Not Equip" : "Take off") | ArmorStyle | size(WIDTH, EQUAL, 8)
							}) | flex,
							vbox({
								text("Accessory"),
								text(player_accessory),
								text(!playerInfo.getAccessory() ? "Not Equip" : "Take off") | AccessoryStyle | size(WIDTH, EQUAL, 8)
								}) | flex,
						}) | flex,
						}) | flex | border
				);
				k++;
			}

			// 背包道具欄
			vector<Elements> grid_items;
			Elements backpack_row;
			int count = 0;
			int i = 0;
			for (auto& item : backpack_items) {
				if (item.second > 0) {
					Elements equipButtons;
					string item_name = StringUtil::getName(item.first);
					ui_items.push_back(item_name);

					for (int j = 0; j < players.size(); j++)
					{
						string button_text = item_name == "Tent" ? "Wear " : "Use ";
						Element equipButton;

						// 3
						//chooseBagItemIndex < (max_length * players.size()) - 1
						if (chooseBagItemIndex == ((i * 3) + j)) {
							equipButton = text(button_text + players[j].getDisplay()) | bgcolor(Color::Green) | size(WIDTH, EQUAL, 11);
						}
						else {
							equipButton = text(button_text + players[j].getDisplay()) | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 11);
						}
						equipButtons.push_back(equipButton);
					}

					backpack_row.push_back(vbox({
						text(item_name),
						text("Quantity: " + to_string(item.second)),
						vbox(equipButtons)
						}) | border | size(WIDTH, GREATER_THAN, 20));
					count++;
					if (count == 4) {
						grid_items.push_back(backpack_row);
						backpack_row.clear();
						count = 0;
					}
					i++;
				}
			}
			if (!backpack_row.empty()) {
				grid_items.push_back(backpack_row);
			}

			return vbox({
			  hbox({
				hbox({
				  text("Bag") | vcenter | flex,
				}) | flex,
				closeButton
			  }),
			  separator(),
				text("A,D: Select Item; Space: Use item; J,L: Select Player Equipment; K: Take off Equipment") | hcenter,
			  text("money: " + to_string(money)) | hcenter,
			  separator(),
			  hbox({
				gridbox(grid_items) | size(WIDTH, EQUAL, 80),
				separator() | size(HEIGHT, GREATER_THAN, 150),
				vbox({
					  playerColumn | flex
				 }) | size(WIDTH, EQUAL, 70)
			   })
				}) | size(WIDTH, GREATER_THAN, 150)
				| size(HEIGHT, GREATER_THAN, 150)
				| border;
			});

		bagComponent |= CatchEvent([&](Event event) {
			if (event.is_character() && event.character() == "a") {
				// 背包欄位移動
				if (chooseBagItemIndex > 0) {
					chooseBagItemIndex -= 1;
				}
			}
			if (event.is_character() && event.character() == "d") {
				// 背包欄位移動
				int max_length = 0;
				for (auto& item : backpack_items) {
					if (item.second > 0) {
						max_length++;
					}
				}
				if (chooseBagItemIndex < (max_length * players.size()) - 1) {
					chooseBagItemIndex += 1;
				}
			}
			if (event.is_character() && event.character() == "j") {
				if (chooseBagPlayerIndex > 0) {
					chooseBagPlayerIndex -= 1;
				}
			}

			if (event.is_character() && event.character() == "l") {
				if (chooseBagPlayerIndex < (this->players.size() * 3) - 1) {
					chooseBagPlayerIndex += 1;
				}
			}
			if (event.is_character() && event.character() == " ") {// 裝備
				wearEquipment();
			}
			if (event.is_character() && event.character() == "k") {// 脫裝備
				takeOffEquipment();
			}

			refreshUI();
			return false;
			});
		return bagComponent;
	}
};
#endif