#ifndef HOLYGRAIL_H
#define HOLYGRAIL_H
#include <string>

#include "Accessory.h"

class HolyGrail: public Accessory
{
public:
    EffectData getEffect() const override
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect + 30,
            pDefenseEffect,
            mDefenseEffect,
            focusEffect
        };
    }

    std::string getName() const override
    {
        return "HolyGrail";
    };
};
#endif