#ifndef CREATURE_H
#define CREATURE_H

#include "../Entity.h"

class Creature : public Entity
{
public :
    int getHp() const
    {
        return hp;
    }

    int getVitality() const
    {
        return vitality;
    }

    int getFocus() const
    {
        return focus;
    }

    int getSpeed() const
    {
        return speed;
    }

    int getHitRate() const
    {
        return hitRate;
    }

    int getPAttack() const
    {
        return pAttack;
    }

    int getMAttack() const
    {
        return mAttack;
    }

    int getPDefense() const
    {
        return pDefense;
    }

    int getMDefense() const
    {
        return mDefense;
    }

protected:
    int hp;
    int vitality;
    int focus;
    int speed;
    int hitRate;
    int pAttack;
    int mAttack;
    int pDefense;
    int mDefense;
};

#endif