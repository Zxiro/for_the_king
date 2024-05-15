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

    static std::string getName() override
    {
        return "LeatherArmor";
    };
};

#endif