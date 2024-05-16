#ifndef CREATURE_H
#define CREATURE_H

#include <ctime>

#include "../Entity.h"

class Creature : public Entity
{
public :
    Creature(const Position &_position, const std::string &_display): Entity(_position, _display)
    {
        srand( time(NULL));
        vitality = rand() % (44 - 30 + 1) + 30;
        focus = 3;
        speed = rand() % (55 - 30 + 1) + 30;
        hitRate = rand() % (60 - 40 + 1) + 40;
        pAttack = rand() % (15 - 5 + 1) + 5;
        mAttack = rand() % (15 - 5 + 1) + 5;
        pDefense = rand() % (20 - 0 + 1) + 0;
        mDefense = rand() % (20 - 0 + 1) + 0;
    }

    virtual double getVitality() const
    {
        return vitality;
    }

    virtual double getFocus() const
    {
        return focus;
    }

    virtual double getSpeed() const
    {
        return speed;
    }

    virtual double getHitRate() const
    {
        return hitRate;
    }

    virtual double getPAttack() const
    {
        return pAttack;
    }

    virtual double getMAttack() const
    {
        return mAttack;
    }

    virtual double getPDefense() const
    {
        return pDefense;
    }

    virtual double getMDefense() const
    {
        return mDefense;
    }
    

protected:
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
