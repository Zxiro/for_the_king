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
private:
    int speedEffect = 0;
    int hitRateEffect = 0;
    int pAttackEffect = 0;
    int mAttackEffect = 0;
    int pDefenseEffect = 0;
    int mDefenseEffect = 0;
    int focusEffect = 0;
};
#endif