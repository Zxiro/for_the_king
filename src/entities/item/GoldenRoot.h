#ifndef GOLDENROOT_H
#define GOLDENROOT_H
#include "Item.h"
#include "../entity/creature/Player.h"

class GoldenRoot : public Item {
public:
    std::string getName() const override {
        return "GoldenRoot";
    }

    void use(Player& player) {
        int newFocus = player.getFocus() + 3;
        if (newFocus > player.getMaxFocus()) {
            newFocus = player.getMaxFocus();
        }
        player.setFocus(newFocus);
    }
};
#endif
