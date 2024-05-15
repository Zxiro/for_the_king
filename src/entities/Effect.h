#ifndef EFFECT_H
#define EFFECT_H
#include "../structs/EffectData.h"

class Effect
{
public:
    virtual EffectData getEffect() const
    {
        return EffectData {
            speedEffect,
            hitRateEffect,
            pAttackEffect,
            mAttackEffect,
            pDefenseEffect,
            mDefenseEffect
        };
    }
private:
    int speedEffect = 0;
    int hitRateEffect = 0;
    int pAttackEffect = 0;
    int mAttackEffect = 0;
    int pDefenseEffect = 0;
    int mDefenseEffect = 0;
};
#endif