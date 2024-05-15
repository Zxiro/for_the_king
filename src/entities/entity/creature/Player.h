#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "../../item/equipment/accessory/Accessory.h"
#include "../../item/equipment/armor/Armor.h"
#include "../../item/equipment/weapon/Weapon.h"

#include <cmath>

class Player : public Creature
{
public:
    void wearWeapon(const Weapon& weapon) const
    {
        *this->weapon = weapon;
    }

    void wearArmor(const Armor& armor) const
    {
        *this->armor = armor;
    }

    void wearAccessory(const Accessory& accessory) const
    {
        *this->accessory = accessory;
    }

    void removeWeapon()
    {
        this->weapon = nullptr;
    }

    void removeArmor()
    {
        this->armor = nullptr;
    }

    void removeAccessory()
    {
        this->accessory = nullptr;
    }

    int getPriority() const
    {
        return std::floor((this->movementCount + 1) / this->speed) * 100;
    }

    int getMaxMovementCount() const
    {
        return std::floor(this->speed / 10);
    }

    double getRollDiceChance() const
    {
        return this->speed / 10;
    }

    void rollDice() const
    {
        this->movementCount += 1;
    }

private:
    Weapon* weapon;
    Armor* armor;
    Accessory* accessory;
    int movementCount = 0;
};

#endif
