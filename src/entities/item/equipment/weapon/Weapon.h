#ifndef WEAPON_H
#define WEAPON_H
#include "../Equipment.h"

class Weapon: public Equipment
{
public:
    Weapon(int diceCount): Equipment(EquipmentType::weapon)
    {
        this->diceCount = diceCount; 
    }

    int getDiceCount() const
    {
        return diceCount;
    }
private:
    int diceCount;
};
#endif