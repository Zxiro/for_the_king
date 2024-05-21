#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <windows.h>

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/component.hpp"

#include "../entities/entity/creature/Player.h"
#include "BagModal.h"
#include "GameColumn.h"
#include "PlayerRow.h"
#include "StoreModal.h"
#include "MapArea.h"

#include "../entities/item/equipment/weapon/Hammer.h"
#include "../entities/item/equipment/armor/PlateArmor.h"
#include "../entities/item/equipment/accessory/HolyGrail.h"

#include "../structs/Position.h"
#include "../entities/entity/Store.h"

using namespace ftxui;
using namespace std;

class MainScreen
{
private:
	Position storePosition;
	Store store;
public:
	MainScreen() : storePosition({ 0, 0 }), store(storePosition) {
	}
	void printUI() {
		ScreenInteractive screen = ScreenInteractive::Fullscreen();
		int sidebar_size = 50;
		int player_row_size = 15;

		// Bag
		bool bag_modal_shown = false;
		auto bag_show_modal = [&] { bag_modal_shown = true; };
		auto bag_hide_modal = [&] { bag_modal_shown = false; };

		BagModal bagModal;
		auto bag_modal_component = bagModal.modalUI(bag_hide_modal);

		// Store
		auto BuyItem = [&]() {
			// ÁÊ¶Rª««~ int money
		};
		bool store_modal_shown = false;
		auto store_show_modal = [&] { store_modal_shown = true; };
		auto store_hide_modal = [&] { store_modal_shown = false; };

		Position storePosition = { 0,0 };
		Store store(storePosition);
		StoreModal storeModal(store, store_hide_modal);
		auto store_modal_component = storeModal.modalUI();

		// Area
		MapArea mapArea;
		PlayerRow playerRow;
		GameColumn gameColumn;
		Component container = mapArea.printUI();
		Component player_row = playerRow.printUI();
		Component sidebar = gameColumn.printUI();
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