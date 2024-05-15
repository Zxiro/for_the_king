#ifndef WOODENSWORD_H
#define WOODENSWORD_H
#include <string>

#include "Weapon.h"

class WoodenSword: public Weapon
{
public:
    WoodenSword(): Weapon(3)
    {
        
    }

    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect + 10,
            pAttackEffect + 5,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect,
        };
    }

    std::string getName() override
    {
        return "WoodenSword";
    };
};

#endif