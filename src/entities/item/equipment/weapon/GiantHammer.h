#ifndef GIANT_HAMMER_H
#define GIANT_HAMMER_H
#include "Weapon.h"

class GiantHammer: public Weapon
{
public:
    GiantHammer(): Weapon(5)
    {
        
    }

    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect - 15,
            pAttackEffect + 20,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect
        };
    }
};

#endif