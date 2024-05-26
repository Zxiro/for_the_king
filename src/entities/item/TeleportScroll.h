#ifndef TELEPORTSCROLL_H
#define TELEPORTSCROLL_H
#include "Item.h"
#include "../entity/creature/Player.h"

class TeleportScroll : public Item {
public:
    std::string getName() const override {
        return "TeleportScroll";
    }
};
#endif
