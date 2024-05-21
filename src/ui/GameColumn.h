#ifndef GAME_COLUMN_H
#define GAME_COLUMN_H

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/mouse.hpp"
#include "ftxui/component/component.hpp"


#include <string>
#include <vector>

class GameColumn
{
private:

public:
	Component printUI() {
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
				hbox({
					text("'Y' Key use Focus"),
					text("'R' Key use Roll"),
				}),
				window(
					text("Helper") | center,
					vbox(
						text("Arrow Key: Move"),
						text("'P' Key: End Turn"),
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
};

#endif