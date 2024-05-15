#ifndef ARMOR_H
#define ARMOR_H
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

    static std::string getName() override
    {
        return "Shoes";
    };
};
#endif