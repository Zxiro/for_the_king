#ifndef ROBE_H
#define ROBE_H
#include <string>

#include "Armor.h"

class LaurelWreath : Armor
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
            mDefenseEffect * 1.1 //TODO: 最終乘算
        };
    }

    std::string getName() override
    {
        return "LaurelWreath";
    };
};

#endif