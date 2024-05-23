#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <windows.h>

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/component.hpp"

#include "modal/BagModal.h"
#include "GameColumn.h"
#include "PlayerRow.h"
#include "modal/StoreModal.h"
#include "MapArea.h"

#include "../structs/Position.h"
#include "../entities/entity/Store.h"

using namespace ftxui;
using namespace std;

class MainScreen
{
private:
	Store* store;
	MapArea mapArea;
	PlayerRow playerRow;
	GameColumn gameColumn;
public:
	MainScreen() {
		store = new Store({ 133, 45 });
	}
	void printUI() {
		ScreenInteractive screen = ScreenInteractive::Fullscreen();
		int sidebar_size = 50;
		int player_row_size = 15;
		bool store_modal_shown = false;
		bool bag_modal_shown = false;

		// Bag
		BagModal bagModal;
		auto bag_modal_component = bagModal.modalUI([&] { bag_modal_shown = false; });

		// Store
		StoreModal storeModal([&] { store_modal_shown = false; });
		auto store_modal_component = storeModal.modalUI();


		// Area
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
				// TODO: 判斷是否能開啟商店

				if (!store_modal_shown) {
					store_modal_shown = true;
				}
			}
			if (event.is_character() && event.character() == "e") {
				if (!bag_modal_shown) {
					bag_modal_shown = true;
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