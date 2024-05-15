#ifndef PLATE_ARMOR_H
#define PLATE_ARMOR_H
#include <string>

#include "Armor.h"

class PlateArmor: Armor
{
public:
    virtual EffectData getEffect() const override
    {
        return EffectData {
            speedEffect - 10,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect + 20,
            mDefenseEffect
        };
    }

    std::string getName() override
    {
        return "PlateArmor";
    };
};

#endif