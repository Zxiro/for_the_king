#ifndef WOODEN_SHIELD_H
#define WOODEN_SHIELD_H
#include <string>

#include "Armor.h"

class WoodenShield: public Armor
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

    std::string getName() const override
    {
        return "WoodenShield";
    };
};

#endif