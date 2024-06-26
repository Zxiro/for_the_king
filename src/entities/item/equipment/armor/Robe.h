#ifndef ROBE_H
#define ROBE_H
#include <string>

#include "Armor.h"

class Robe: public Armor
{
public:
    virtual EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect + 10,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "Robe";
    };
};

#endif