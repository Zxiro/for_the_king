#ifndef HAMMER_H
#define HAMMER_H
#include <string>

#include "Weapon.h"

class Hammer: public Weapon
{
public:
    Hammer(): Weapon(4)
    {
        
    }

    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect - 15,
            pAttackEffect + 15,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "Hammer";
    };
};

#endif