#ifndef MAPAREA_H
#define MAPAREA_H

#include <math.h>
#include <random>


class MapArea
{
private:

public:
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

	Component printUI() {
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
};

#endif