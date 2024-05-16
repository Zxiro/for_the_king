#ifndef MAGIC_WAND_H
#define MAGIC_WAND_H
#include <string>

#include "Weapon.h"

class MagicWand: public Weapon
{
public:
    MagicWand(): Weapon(3)
    {
        
    }

    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect + 10,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "MagicWand";
    };
};

#endif