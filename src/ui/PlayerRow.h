#ifndef PLAYEROW_H
#define PLAYEROW_H

#include "../manager/GameManager.h"
#include "../manager/Singleton.h"

#include "../utils/StringUtil.h"


class PlayerRow
{
private:
	vector<Player> players;
public:
	PlayerRow() {
		players = Singleton<GameManager>::instance().players;
	};

	Element createPlayerElement(int index) {
		Player player = players[index];
		Elements elements;
		string player_weapon = (player.getWeapon() == nullptr) ? "" : player.getWeapon()->getName();
		string player_armor = (player.getArmor() == nullptr) ? "" : player.getArmor()->getName();
		string player_accessory = (player.getAccessory() == nullptr) ? "" : player.getAccessory()->getName();
		elements.push_back(text("Name: " + player.getDisplay()));
		elements.push_back(text("HP: " + StringUtil::toStringFixed(player.getVitality(), 0) + "/" + StringUtil::toStringFixed(player.getVitality(), 0)));
		elements.push_back(text("Focus: " + StringUtil::toStringFixed(player.getFocus(), 0) + "/" + StringUtil::toStringFixed(player.getFocus(), 0)));
		elements.push_back(text("Physical ATK: " + StringUtil::toStringFixed(player.getPAttack(), 0)));
		elements.push_back(text("Physical DEF: " + StringUtil::toStringFixed(player.getPDefense(), 0)));
		elements.push_back(text("Magical ATK: " + StringUtil::toStringFixed(player.getMAttack(), 0)));
		elements.push_back(text("Magical DEF: " + StringUtil::toStringFixed(player.getMDefense(), 0)));
		elements.push_back(text("Speed: " + StringUtil::toStringFixed(player.getSpeed(), 0)));
		elements.push_back(text("HitRate: " + StringUtil::toStringFixed(player.getHitRate(), 0)));
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
	Component printUI() {
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
};

#endif