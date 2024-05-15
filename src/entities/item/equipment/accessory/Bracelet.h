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

    static std::string getName() override
    {
        return "Bracelet";
    };
};
#endif