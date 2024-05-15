#ifndef LEATHER_ARMOR_H
#define LEATHER_ARMOR_H
#include <string>

#include "Armor.h"

class LeatherArmor: Armor
{
public:
    virtual EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect + 5,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "LeatherArmor";
    };
};

#endif