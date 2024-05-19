#ifndef SHOES_H
#define SHOES_H
#include <string>

#include "Accessory.h"

class Shoes: public Accessory
{
public:
    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect + 5,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "Shoes";
    };
};
#endif