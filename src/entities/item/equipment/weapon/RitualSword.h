#ifndef RITUAL_SWORD_H
#define RITUAL_SWORD_H
#include <string>

#include "Weapon.h"

class RitualSword: public Weapon
{
public:
    RitualSword(): Weapon(1)
    {
        
    }

    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect + 15,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "RitualSword";
    };
};

#endif