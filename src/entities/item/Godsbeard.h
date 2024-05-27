#ifndef GODSBEARD_H
#define GODSBEARD_H
#include "Item.h"
#include "../entity/creature/Player.h"

class GodsBeard : public Item {
public:
    std::string getName() const override {
        return "GodsBeard";
    }
};
#endif
