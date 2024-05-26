#ifndef GODSBEARD_H
#define GODSBEARD_H
#include "Item.h"
#include "../entity/creature/Player.h"

class Godsbeard : public Item {
public:
    std::string getName() const override {
        return "Godsbeard";
    }

    void use(Player& player) {
        int newVitality = player.getVitality() + 25;
        if (newVitality > player.getMaxVitality()) {
            newVitality = player.getMaxVitality();
        }
        player.setVitality(newVitality);
    }
};
#endif
