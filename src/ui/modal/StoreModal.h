#ifndef STOREMODAL_H
#define STOREMODAL_H

#include "../../entities/entity/creature/Player.h"
#include "../../manager/BackpackManager.h"
#include "../../manager/GameManager.h"

using namespace std;

class StoreModal {
private:
  ButtonOption button_style;
  int chooseStoreIndex;
  Store *store;
  function<void()> hide_modal;
  map<std::type_index, int> store_items;

public:
  StoreModal(const function<void()> _hide_modal) {
    this->store = new Store();
    this->hide_modal = _hide_modal;
    button_style = ButtonOption::Animated();
    this->store_items = this->store->getItems();
    this->chooseStoreIndex = 0;
  }

  Component modalUI() {

    auto storeComponent =
        Container::Vertical({Button("X", hide_modal, button_style)});

    storeComponent |= Renderer([&](Element closeButton) {
      int money = Singleton<BackpackManager>::instance().getMoney();
      // items
      vector<Elements> grid_items;
      Elements store_row;
      int count = 0;
      int i = 0;
      for (auto &item : store_items) {
        Element buyButton;
        if (chooseStoreIndex == i) {
          buyButton =
              text("Buy") | bgcolor(Color::Green) | size(WIDTH, EQUAL, 2);
        } else {
          buyButton =
              text("Buy") | bgcolor(Color::GrayDark) | size(WIDTH, EQUAL, 2);
        }
        store_row.push_back(
            vbox({// text(item.first),
                  text("amount: " + to_string(item.second)), buyButton}) |
            border | size(WIDTH, GREATER_THAN, 20));
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

      return vbox({hbox({
                       hbox({
                           text("Store") | vcenter | flex,
                       }) | flex,
                       closeButton,
                   }),
                   separator(), text("money: " + to_string(money)) | hcenter,
                   separator(),
                   hbox({
                       gridbox(grid_items) | flex,
                   })}) |
             size(WIDTH, GREATER_THAN, 80) | size(HEIGHT, GREATER_THAN, 100) |
             border;
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
        int money = Singleton<BackpackManager>::instance().getMoney();
        auto it = store_items.begin();
        std::advance(it, chooseStoreIndex);
        if (it != store_items.end()) {
          string itemName = it->first.name();
          if (money >= it->second) {
            store->buyItem(itemName);
          }
        }
      }
      return false;
    });
    return storeComponent;
  }
};
#endif