#ifndef BRACELET_H
#define BRACELET_H
#include <string>

#include "Accessory.h"

class Bracelet: public Accessory
{
public:
    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect + 1
        };
    }

    std::string getName() const override
    {
        return "Bracelet";
    };
};
#endif