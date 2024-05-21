#ifndef BAGMODAL_H
#define BAGMODAL_H

#include "../entities/Backpack.h"

class BagModal
{
private:
	Backpack* backpack;
	int chooseBagPlayerIndex;
	int chooseBagItemIndex;
public:
	BagModal() {
		chooseBagPlayerIndex = 0;
		chooseBagItemIndex = 0;
		this->backpack = Singleton<GameManager>::instance().backpack;
	}
	Component modalUI(std::function<void()> hide_modal) {
		auto bagComponent = Button("X", hide_modal);

		bagComponent |= Renderer([&](Element closeButton) {
			map<type_index, int> backpack_items = Singleton<GameManager>::instance().backpack->getItems();
			int money = Singleton<GameManager>::instance().backpack->getMoney();
			vector<Player> players = Singleton<GameManager>::instance().players;
			
			// 玩家資訊
			Elements playerColumn;
			int k = 0;
			for (auto& playerInfo : players)
			{
				string player_weapon = "";
				if(playerInfo.getWeapon() != nullptr) {
					playerInfo.getWeapon()->getName();
				}
				string player_armor = (playerInfo.getArmor() == nullptr) ? "" : playerInfo.getArmor()->getName();
				string player_accessory = (playerInfo.getAccessory() == nullptr) ? "" : playerInfo.getAccessory()->getName();

				Elements takeOffButtons;
				for (int l = 0; l < 3; l++)
				{
					Element takeOffButton;
					if (chooseBagPlayerIndex == ((k * 3) + l)) {
					}
					else {
						takeOffButton = text("Take off") | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 6);
					}
					takeOffButtons.push_back(takeOffButton);
				}
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
								text("Take off") | WeaponStyle | size(WIDTH, EQUAL, 6)
							}) | flex,
							vbox({
								text("Armor"),
								text(player_armor),
								text("Take off") | ArmorStyle | size(WIDTH, EQUAL, 6)
							}) | flex,
							vbox({
								text("Accessory"),
								text(player_accessory),
								text("Take off") | AccessoryStyle | size(WIDTH, EQUAL, 6)
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
					string item_name = item.first.name();
					size_t pos = item_name.find("class ");

					if (pos != string::npos) {
						item_name = item_name.substr(pos + 6);
					}

					for (int j = 0; j < players.size(); j++)
					{
						string button_text = "Equip ";

						Element equipButton;
						if (item_name == "Tent") {
							button_text = "Use   ";
						}
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
						text("amount: " + to_string(item.second)),
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
			  text("Do not take off your equipment during combat") | hcenter,
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
				map<type_index, int> backpack_items = Singleton<GameManager>::instance().backpack->getItems();

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
			if (event.is_character() && event.character() == "j") {// 左箭頭[D
				if (chooseBagPlayerIndex > 0) {
					chooseBagPlayerIndex -= 1;
				}
			}

			if (event.is_character() && event.character() == "l") {// 右箭頭[C
				if (chooseBagPlayerIndex < (players.size() * 3) - 1) {
					chooseBagPlayerIndex += 1;
				}
			}
			if (event.is_character() && event.character() == " ") {// 裝備
				vector<Player> players = Singleton<GameManager>::instance().players;
				int typeIndex = chooseBagItemIndex / 3;
				int playerIndex = chooseBagItemIndex % 3;
				map<type_index, int> backpack_items = Singleton<GameManager>::instance().backpack->getItems();
				auto it = backpack_items.begin();
				advance(it, typeIndex);
				if (it == backpack_items.end()) {
					return false;
				}

				auto* item = EquipFactory::instance().createInstance(it->first);
				auto type_ptr = std::unique_ptr<Equipment>(item);
				Weapon* weapon = dynamic_cast<Weapon*>(type_ptr.get());

				// 擷取名稱
				string item_name = it->first.name();
				size_t pos = item_name.find("class ");
				if (pos != string::npos) {
					item_name = item_name.substr(pos + 6);
				}

				if (item_name != "Tent") {
					if (Weapon* weaponPtr = dynamic_cast<Weapon*>(item)) {// 裝備後讀取壞掉
						if (Singleton<GameManager>::instance().players[playerIndex].getWeapon() == nullptr) {
							Singleton<GameManager>::instance().players[playerIndex].wearWeapon(weapon);
						}
					}
				} else {
					// 使用道具(還沒好)
				}
			}
			if (event.is_character() && event.character() == "u") {
				vector<Player> players = Singleton<GameManager>::instance().players;
				// 卸下裝備
				int typeIndex = chooseBagPlayerIndex % 3;
				int playerIndex = chooseBagPlayerIndex / 3;
				if (typeIndex == 0) { // weapon
					if (players[playerIndex].getWeapon() != nullptr) {
						players[playerIndex].removeWeapon();
					}
				}
				else if (typeIndex == 1) { // armor
					if (players[playerIndex].getArmor() != nullptr) {
						players[playerIndex].removeArmor();
					}
				}
				else if (typeIndex == 2) { // accessory
					if (players[playerIndex].getAccessory() != nullptr) {
						players[playerIndex].removeAccessory();
					}
				}
			}
			return false;
			});

		return bagComponent;
	}
};
#endif