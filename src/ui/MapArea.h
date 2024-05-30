#ifndef MAPAREA_H
#define MAPAREA_H

#include "../manager/GameManager.h"
#include <random>

class MapArea {
private:
  vector<vector<string>> getMap() {
    auto entityMap = Singleton<GameManager>::instance().map->getMap();
    vector<vector<string>> res;

    for (int i = 0; i < entityMap.size(); ++i) {
      vector<string> cell;
      for (int j = 0; j < entityMap[0].size(); ++j) {
        cell.push_back(entityMap[i][j]->getDisplay());
      }
      res.push_back(cell);
    }
    return res;
  }

public:
  Component printUI() {
    auto gameMap = getMap();
    Elements map_elements;
    for (const auto &row : gameMap) {
      Elements row_elements;
      for (const auto &cell : row) {
        Color ui_color = Color::Default;

        if (cell == ".") {
          ui_color = Color::Yellow;
        } else if (cell == "?") {
          ui_color = Color::White;
        } else if (cell == "1") {
          ui_color = Color::White;
        } else if (cell == "$") {
          ui_color = Color::LightYellow3;
        } else if (cell == " ") {
          ui_color = Color::GrayDark;
        } else if (cell == "E") {
          ui_color = Color::Red;
        }

        if (cell == "1" || cell == "?" || cell == "E") {
          row_elements.push_back(text(cell) | color(ui_color) |
                                 bgcolor(Color::Yellow));
        } else {
          row_elements.push_back(text(cell) | bgcolor(ui_color) |
                                 color(Color::Black));
        }
      }
      map_elements.push_back(hbox(row_elements));
    }

    Component map_area =
        Renderer([map_elements] { return vbox(map_elements); });
    Component container = map_area;
    return container;
  }
};

#endif