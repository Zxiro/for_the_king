#ifndef TENT_H
#define TENT_H
#include "Item.h"
#include "../entity/Entity.h"
#include "../entity/creature/Player.h"

class Tent : public Entity, public Item {
public:
    Tent()
        : Entity(Position(), "Tent"), placedByPlayerIndex(-1), turnCounter(0) {}
    
    Tent(const Position& position)
        : Entity(position, "Tent"), placedByPlayerIndex(-1), turnCounter(0) {}

    std::string getName() const override {
        return "Tent";
    }

    void setPlacedByPlayerIndex(int index) {
        placedByPlayerIndex = index;
    }

    void incrementTurnCounter() {
        turnCounter++;
    }

    bool shouldRemove() const {
        return turnCounter > 0;
    }

    bool isPassable() const override {
        return true;
    }

    bool canTeleport() const override {
        return true; // 可以傳送到Tent上
    }

    void healPlayer(Player& player) const {
        int newVitality = player.getVitality() + 50;
        if (newVitality > player.getMaxVitality()) {
            newVitality = player.getMaxVitality();
        }
        player.setVitality(newVitality);

        int newFocus = player.getFocus() + 5;
        if (newFocus > player.getMaxFocus()) {
            newFocus = player.getMaxFocus();
        }
        player.setFocus(newFocus);
    }

private:
    int placedByPlayerIndex;
    int turnCounter;
};

#endif // TENT_H