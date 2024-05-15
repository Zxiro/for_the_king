#ifndef WOODEN_SHIELD_H
#define WOODEN_SHIELD_H
#include <string>

#include "Armor.h"

class WoodenSword: Armor
{
public:
    virtual EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect + 10,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    static std::string getName() override
    {
        return "WoodenSword";
    };
};

#endif