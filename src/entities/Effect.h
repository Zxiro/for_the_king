#ifndef EFFECT_H
#define EFFECT_H
#include "../exception/UnImplementException.h"
#include "../structs/EffectData.h"

class Effect
{
public:
    virtual EffectData getEffect() const
    {
        throw UnImplementException();
    }
public:
    double speedEffect = 0;
    double hitRateEffect = 0;
    double pAttackEffect = 0;
    double mAttackEffect = 0;
    double pDefenseEffect = 0;
    double mDefenseEffect = 0;
    double focusEffect = 0;
};
#endif