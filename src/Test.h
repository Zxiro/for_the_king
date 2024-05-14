#ifndef TEST_H
#define TEST_H

#include <memory>
#include <random>
#include <windows.h>

#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/component_options.hpp>
#include <functional>
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;
using namespace std;

struct PlayerInfoType {
	string name;
	string hp;
	string max_hp;
	string focus;
	string max_focus;
	string physical_atk;
	string physical_def;
	string magical_atk;
	string magical_def;
	string speed;
	string hitrate;
	string weapon;
	string armor;
	string accessory;
	vector<string> buff;
};

class Test {
	// Player
	int randomInt(int min, int max) {
		random_device rd;
		mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
		uniform_int_distribution<int> dis(min, max);
		return dis(gen);
	}

	vector<PlayerInfoType> generatePlayerInfo() {
		vector<PlayerInfoType>players;
		for (int i = 0; i < 3; i++)
		{
			int hp = randomInt(30, 44);
			players.push_back({
				"player" + to_string(i + 1),
				to_string(hp),
				to_string(hp),
				to_string(3),
				to_string(3),
				to_string(randomInt(5, 14)),
				to_string(randomInt(0, 19)),
				to_string(randomInt(5, 14)),
				to_string(randomInt(0, 19)),
				to_string(randomInt(30, 54)),
				to_string(randomInt(40, 59)),
				"",
				"",
				"",
				{"buff1", "buff2", "buff3"} // buff
				});
		}
		return players;
	}

	Element createPlayerElement(const PlayerInfoType& playerInfo) {
		Elements elements;
		elements.push_back(text("Name: " + playerInfo.name));
		elements.push_back(text("HP: " + playerInfo.hp + "/" + playerInfo.max_hp));
		elements.push_back(text("Focus: " + playerInfo.focus + "/" + playerInfo.max_focus));
		elements.push_back(text("Physical ATK: " + playerInfo.physical_atk));
		elements.push_back(text("Physical DEF: " + playerInfo.physical_def));
		elements.push_back(text("Magical ATK: " + playerInfo.magical_atk));
		elements.push_back(text("Magical DEF: " + playerInfo.magical_def));
		elements.push_back(text("Speed: " + playerInfo.speed));
		elements.push_back(text("HitRate: " + playerInfo.hitrate));
		elements.push_back(text("Weapon: " + playerInfo.weapon));
		elements.push_back(text("Armor: " + playerInfo.armor));
		elements.push_back(text("Accessory: " + playerInfo.accessory));
		std::string buffs = "Buff: ";
		for (const auto& buff : playerInfo.buff) {
			buffs += buff + ", ";
		}
		if (!playerInfo.buff.empty()) {
			buffs.pop_back();
			buffs.pop_back();
		}
		elements.push_back(text(buffs));

		return vbox(move(elements));
	}

	Component printPlayerRowUI() {
		int chooseIndex = 0;
		std::vector<PlayerInfoType> playerInfos = generatePlayerInfo();
		Elements players;
		for (size_t i = 0; i < playerInfos.size(); ++i) {
			if (chooseIndex == i) {
				players.push_back(createPlayerElement(playerInfos[i]) | borderStyled(LIGHT, Color::Green) | flex);
			}
			else {
				players.push_back(createPlayerElement(playerInfos[i]) | border | flex);
			}
		}

		return Renderer([players = move(players)]{
			return hbox(move(players));
			});
	}

	// Sidebar
	Component printSidebarUI() {
		// fake data
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
					hbox(move(action_elements)),
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
	vector<vector<string>> generateFakeMap() {
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
		vector<vector<string>> fake_map = generateFakeMap();
		Elements map_elements;
		for (const auto& row : fake_map) {
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

	Component ModalComponent(std::function<void()> do_nothing,
		std::function<void()> hide_modal) {
		auto component = Container::Vertical({
			Button("Do nothing", do_nothing),
			Button("Quit modal", hide_modal),
			});
		component |= Renderer([&](Element inner) {
			return vbox({
					   text("Modal component "),
					   separator(),
					   inner,
				})
				| size(WIDTH, GREATER_THAN, 30)
				| border;
			});
		return component;
	}

	public:
		void printUI() {
			ScreenInteractive screen = ScreenInteractive::Fullscreen();
			int sidebar_size = 50;
			int player_row_size = 15;

			Component container = printMapUI();
			Component player_row = printPlayerRowUI();
			Component sidebar = printSidebarUI();

			container = ResizableSplitRight(sidebar, container, &sidebar_size);
			container = ResizableSplitBottom(player_row, container, &player_row_size);

			Component renderer = Renderer(container, [&] {
				return container->Render() | border;
				});
			screen.Loop(renderer);
		}
};

#endif