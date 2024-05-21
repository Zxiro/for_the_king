#ifndef TEST_H
#define TEST_H

#include <memory>
#include <random>
#include <windows.h>

#include "utils/StringUtil.h"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/component_options.hpp>
#include <functional>
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include <math.h>

#include "entities/entity/creature/Player.h"
#include "entities/item/equipment/weapon/WoodenSword.h"
#include "entities/item/equipment/weapon/Hammer.h"
#include "entities/item/equipment/armor/LeatherArmor.h"
#include "entities/item/equipment/accessory/HolyGrail.h"
#include "entities/Backpack.h"
#include "entities/entity/Store.h"
#include "entities/item/equipment/accessory/HolyGrail.h"
#include "entities/item/equipment/armor/PlateArmor.h"
#include "manager/GameManager.h"

using namespace ftxui;
using namespace std;

auto button_style = ButtonOption::Animated();


Position storePosition = { 0,0 };
Store store(storePosition);

std::vector<Player> players;

std::map<std::type_index, int> store_items = store.getItems();
int chooseStoreIndex = 0;
int chooseBagItemIndex = 0;
int chooseBagPlayerIndex = 0;



class Test
{
	// Player
	void createPlayers() {
		for (int index = 0; index < 3; ++index) {
			Player player(Position{ index + 1, 2 }, "Player" + std::to_string(index + 1));
			// Sleep(1000); 防止資料重疊
			Hammer* hammer = new Hammer();
			player.wearWeapon(hammer);
			
			PlateArmor* plateArmor = new PlateArmor();
			player.wearArmor(plateArmor);

			HolyGrail* holyGrail = new HolyGrail();
			player.wearAccessory(holyGrail);

			players.push_back(player);
		}
	}

	Element createPlayerElement(int index) {
		Player player = players[index];
		Elements elements;
		string player_weapon = (player.getWeapon() == nullptr) ? "" : player.getWeapon()->getName();
		string player_armor = (player.getArmor() == nullptr) ? "" : player.getArmor()->getName();
		string player_accessory = (player.getAccessory() == nullptr) ? "" : player.getAccessory()->getName();
		elements.push_back(text("Name: " + player.getDisplay()));
		elements.push_back(text("HP: " + StringUtil::toStringFixed(player.getVitality(), 0) + "/" + to_string(player.getVitality())));
		elements.push_back(text("Focus: " + to_string(player.getFocus()) + "/" + to_string(player.getFocus())));
		elements.push_back(text("Physical ATK: " + to_string(player.getPAttack())));
		elements.push_back(text("Physical DEF: " + to_string(player.getPDefense())));
		elements.push_back(text("Magical ATK: " + to_string(player.getMAttack())));
		elements.push_back(text("Magical DEF: " + to_string(player.getMDefense())));
		elements.push_back(text("Speed: " + to_string(player.getSpeed())));
		elements.push_back(text("HitRate: " + to_string(player.getHitRate())));
		elements.push_back(text("Weapon: " + player_weapon));
		elements.push_back(text("Armor: " + player_armor));
		elements.push_back(text("Accessory: " + player_accessory));
		std::string buffs = "Buff: ";
		//for (const auto& buff : playerInfo.buff) {
		//	buffs += buff + ", ";
		//}
		//if (!playerInfo.buff.empty()) {
		//	buffs.pop_back();
		//	buffs.pop_back();
		//}
		elements.push_back(text(buffs));

		return vbox(move(elements));
	}

	Component printPlayerRowUI() {
		int chooseIndex = 0;// 還沒寫遊戲狀態 所以暫時用假選擇
		Elements playersElements;
		for (int i = 0; i < 3; ++i) {
			if (chooseIndex == i) {
				playersElements.push_back(createPlayerElement(i) | borderStyled(LIGHT, Color::Green) | flex);
			}
			else {
				playersElements.push_back(createPlayerElement(i) | border | flex);
			}
		}

		return Renderer([playersElements = move(playersElements)]{
			return hbox(playersElements);
			});
	}

	// Sidebar
	Component printGameColumnUI() {
		// fake data(因為遊戲狀態還沒好)
		int turn = 1;
		string playerName = "Player1";
		int total_action_point = 8;
		int action_point = 7;

		Elements action_elements;
		action_elements.push_back(text("Action Point: "));
		for (size_t i = 0; i < total_action_point; i++)
		{
			if (i < (total_action_point - action_point)) {
				action_elements.push_back(text("*") | color(Color::Red));
			}
			else {
				action_elements.push_back(text("*") | color(Color::GrayLight));
			}
		}

		return Renderer([turn, playerName, action_elements] {
			return vbox({
				vbox({
					text("Turn: " + to_string(turn)),
					text("PlayerName: " + playerName),
					hbox(action_elements),
				}) | flex,
				window(
					text("Helper") | center,
					vbox(
						text("Arrow Key: Move"),
						text("'P' Kye: End Turn"),
						text("'I' Key: Open Bag"),
						hbox({
							text(" ") | bgcolor(Color::RGB(110, 110, 114)),text(":Wall, "),
							text(".") | bgcolor(Color::RGB(177, 159, 15)),text(":Road, "),
							text("$") | bgcolor(Color::RGB(243, 242, 188)),text(":Shop"),
							})
					)
				)
				});
			});
	}

	// Map
	vector<vector<string>> generateMap() {
		// GameMap gameMap(140, 50);
		vector<vector<string>> fake_map(140, vector<string>(140, "."));

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis_row(0, 139);
		uniform_int_distribution<int> dis_col(0, 139);
		int row_1 = dis_row(gen);
		int col_1 = dis_col(gen);

		for (int i = 0; i < 5; ++i) {
			int row_$ = dis_row(gen);
			int col_$ = dis_col(gen);
			fake_map[row_$][col_$] = "$";
		}

		for (int i = 0; i < 5; ++i) {
			int row_quest = dis_row(gen);
			int col_quest = dis_col(gen);
			fake_map[row_quest][col_quest] = "?";
		}

		for (int i = 0; i < 3; ++i) {
			int row_quest = dis_row(gen);
			int col_quest = dis_col(gen);
			fake_map[row_quest][col_quest] = "E";
		}

		for (int i = 0; i < 20; ++i) {
			int row_space = dis_row(gen);
			int col_space = dis_col(gen);
			fake_map[row_space][col_space] = " ";
		}
		fake_map[row_1][col_1] = "1";

		return fake_map;
	}

	Component printMapUI() {
		//GameManager manager;
		auto gameMap = generateMap();
		//manager.map = gameMap;
		Elements map_elements;
		for (const auto& row : gameMap) {
			Elements row_elements;
			for (const auto& cell : row) {
				Color ui_color = Color::Default;

				if (cell == ".") {
					ui_color = Color::Yellow;
				}
				else if (cell == "?") {
					ui_color = Color::White;
				}
				else if (cell == "1") {
					ui_color = Color::White;
				}
				else if (cell == "$") {
					ui_color = Color::LightYellow3;
				}
				else if (cell == " ") {
					ui_color = Color::GrayDark;
				}
				else if (cell == "E") {
					ui_color = Color::Red;
				}

				if (cell == "1" || cell == "?" || cell == "E") {
					row_elements.push_back(text(cell) | color(ui_color) | bgcolor(Color::Yellow));
				}
				else {
					row_elements.push_back(text(cell) | bgcolor(ui_color) | color(Color::Black));
				}
			}
			map_elements.push_back(hbox(row_elements));
		}

		Component map_area = Renderer([map_elements] {
			return vbox(map_elements);
			});
		Component container = map_area;
		return container;
	}

	Component BagModal(std::function<void()> hide_modal) {
		auto bagComponent = Button("X", hide_modal);

		bagComponent |= Renderer([&](Element closeButton) {
			map<type_index, int> backpack_items = Singleton<GameManager>::instance().backpack->getItems();
			int money = Singleton<GameManager>::instance().backpack->getMoney();

			// player(RightColumn)
			Elements playerColumn;
			int k = 0;
			for (auto& playerInfo : players)
			{
				string player_weapon = (playerInfo.getWeapon() == nullptr) ? "" : playerInfo.getWeapon()->getName();
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

			// items(LeftColumn)
			vector<Elements> grid_items;
			Elements backpack_row;
			int count = 0;
			int i = 0;
			for (auto& item : backpack_items) {
				if (item.second > 0) {
					Elements equipButtons;
					for (int j = 0; j < players.size(); j++)
					{
						Element equipButton;
						if (chooseBagItemIndex == ((i * 3) + j)) {
							equipButton = text("Equip" + players[j].getDisplay()) | bgcolor(Color::Green) | size(WIDTH, EQUAL, 10);
						}
						else {
							equipButton = text("Equip" + players[j].getDisplay()) | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 10);
						}
						equipButtons.push_back(equipButton);
					}

					backpack_row.push_back(vbox({
						text(item.first.name()),
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
			if (event.is_character() && event.character() == " ") {
				// 裝備
			}
			if (event.is_character() && event.character() == "u") {
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

	Component StoreModal(std::function<void()> hide_modal,
		std::function<void()> buyItem
	) {
		auto storeComponent = Container::Vertical({
			Button("X", hide_modal, button_style)
			});

		storeComponent |= Renderer([&](Element closeButton) {
			int money = Singleton<GameManager>::instance().backpack->getMoney();
			// items
			vector<Elements> grid_items;
			Elements store_row;
			int count = 0;
			int i = 0;
			for (auto& item : store_items) {
				Element buyButton;
				if (chooseStoreIndex == i) {
					buyButton = text("Buy") | bgcolor(Color::Green) | size(WIDTH, EQUAL, 2);
				}
				else {
					buyButton = text("Buy") | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 2);
				}
				store_row.push_back(vbox({
					//text(item.first),
					text("amount: " + to_string(item.second)),
					buyButton
					}) | border | size(WIDTH, GREATER_THAN, 20));
				count++;
				if (count == 4) {
					grid_items.push_back(store_row);
					store_row.clear();
					count = 0;
				}
				i++;
			}
			if (!store_row.empty()) {
				grid_items.push_back(store_row);
			}

			return vbox({
					   hbox({
							hbox({
							text("Store") | vcenter | flex,
							}) | flex,
							closeButton,
						}),
					   separator(),
					   text("money: " + to_string(money)) | hcenter,
					   separator(),
					   hbox({
							gridbox(grid_items) | flex,
						  })
				})
				| size(WIDTH, GREATER_THAN, 80)
				| size(HEIGHT, GREATER_THAN, 100)
				| border;
			});
		storeComponent |= CatchEvent([&](Event event) {
			if (event.is_character() && event.character() == "w") {
			}
			if (event.is_character() && event.character() == "a") {
				if (chooseStoreIndex > 0) {
					chooseStoreIndex -= 1;
				}
			}
			if (event.is_character() && event.character() == "s") {
			}
			if (event.is_character() && event.character() == "d") {
				if (chooseStoreIndex < store_items.size() - 1) {
					chooseStoreIndex += 1;
				}
			}
			if (event.is_character() && event.character() == " ") {
				// 購買
				int money = Singleton<GameManager>::instance().backpack->getMoney();
				auto it = store_items.begin();
				std::advance(it, chooseStoreIndex);
				if (it != store_items.end()) {
					string itemName = it->first.name();
					if (money >= it->second) {
						store.buyItem(itemName);
					}
				}
			}
			return false;
			});
		return storeComponent;
	}


public:
	Test() {
		createPlayers();
	}
	void printUI() {
		ScreenInteractive screen = ScreenInteractive::Fullscreen();
		int sidebar_size = 50;
		int player_row_size = 15;

		// Bag
		bool bag_modal_shown = false;
		auto bag_show_modal = [&] { bag_modal_shown = true; };
		auto bag_hide_modal = [&] { bag_modal_shown = false; };

		auto bag_modal_component = BagModal(bag_hide_modal);

		// Store
		auto BuyItem = [&]() {
			// 購買物品 int money
		};
		bool store_modal_shown = false;
		auto store_show_modal = [&] { store_modal_shown = true; };
		auto store_hide_modal = [&] { store_modal_shown = false; };
		auto store_modal_component = StoreModal(store_hide_modal, BuyItem);

		// Area
		Component container = printMapUI();
		Component player_row = printPlayerRowUI();
		Component sidebar = printGameColumnUI();
		Sleep(3000);
		container = ResizableSplitRight(sidebar, container, &sidebar_size);
		container = ResizableSplitBottom(player_row, container, &player_row_size);
		container |= Modal(bag_modal_component, &bag_modal_shown);
		container |= Modal(store_modal_component, &store_modal_shown);

		// Get KeyBoard Event
		container |= CatchEvent([&](Event event) {
			if (event.is_character() && event.character() == "i") {
				if (!store_modal_shown) {
					bag_show_modal();
				}
			}
			if (event.is_character() && event.character() == "e") {
				if (!bag_modal_shown) {
					store_show_modal();
				}
			}
			return false;
			});

		Component renderer = Renderer(container, [&] {
			return container->Render() | border;
			});
		screen.Loop(renderer);
	}
};

#endif