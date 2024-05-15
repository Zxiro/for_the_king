#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "../../item/equipment/accessory/Accessory.h"
#include "../../item/equipment/armor/Armor.h"
#include "../../item/equipment/weapon/Weapon.h"

#include <cmath>

#include "../../../utils/EffectUtil.h"

class Player : public Creature
{
public:
    void wearWeapon(const Weapon& weapon) const
    {
        *this->weapon = weapon;
    }

    void wearArmor(const Armor& armor) const
    {
        *this->armor = armor;
    }

    void wearAccessory(const Accessory& accessory) const
    {
        *this->accessory = accessory;
    }

    void removeWeapon()
    {
        this->weapon = nullptr;
    }

    void removeArmor()
    {
        this->armor = nullptr;
    }

    void removeAccessory()
    {
        this->accessory = nullptr;
    }

    int getPriority() const
    {
        return std::floor((this->movementCount + 1) / this->speed) * 100;
    }

    int getMaxMovementCount() const
    {
        return std::floor(this->speed / 10);
    }

    double getRollDiceChance() const
    {
        return this->speed / 10;
    }

    void rollDice() const
    {
    }

    virtual double getVitality() const override
    {
        return vitality;
    }

    virtual double getFocus() const override
    {
        int effect = EffectUtil<Weapon>::getFocus(this->weapon);
        effect += EffectUtil<Armor>::getFocus(this->armor);
        effect += EffectUtil<Accessory>::getFocus(this->accessory);
        return focus + effect;
    }

    virtual double getSpeed() const override
    {
        int effect = EffectUtil<Weapon>::getSpeed(this->weapon);
        effect += EffectUtil<Armor>::getSpeed(this->armor);
        effect += EffectUtil<Accessory>::getSpeed(this->accessory);
        return speed + effect;
    }

    virtual double getHitRate() const override
    {
        int effect = EffectUtil<Weapon>::getHitRate(this->weapon);
        effect += EffectUtil<Armor>::getHitRate(this->armor);
        effect += EffectUtil<Accessory>::getHitRate(this->accessory);
        return hitRate + effect;
    }

    virtual double getPAttack() const override
    {
        int effect = EffectUtil<Weapon>::getPAttack(this->weapon);
        effect += EffectUtil<Armor>::getPAttack(this->armor);
        effect += EffectUtil<Accessory>::getPAttack(this->accessory);
        return pAttack + effect;
    }

    virtual double getMAttack() const override
    {
        int effect = EffectUtil<Weapon>::getMAttack(this->weapon);
        effect += EffectUtil<Armor>::getMAttack(this->armor);
        effect += EffectUtil<Accessory>::getMAttack(this->accessory);
        return mAttack + effect;
    }

    virtual double getPDefense() const override
    {
        int effect = EffectUtil<Weapon>::getPDefense(this->weapon);
        effect += EffectUtil<Armor>::getPDefense(this->armor);

        int accessoryPDefense = EffectUtil<Accessory>::getPDefense(this->accessory);
        int res = 0;
        // 特別處理，寫法很差，目前想不到更好的寫法
        if (accessory->getName() != "LaurelWreath")
        {
            effect += accessoryPDefense;
            res = pDefense + effect + accessoryPDefense;
        } else
        {
            res = (pDefense + effect) * accessoryPDefense;
        }
        
        return res;
    }

    virtual double getMDefense() const override
    {
        int effect = EffectUtil<Weapon>::getMDefense(this->weapon);
        effect += EffectUtil<Armor>::getMDefense(this->armor);
        effect += EffectUtil<Accessory>::getMDefense(this->accessory);
        return mDefense + effect;
    }

private:
    Weapon* weapon;
    Armor* armor;
    Accessory* accessory;
    int movementCount = 0;
};

#endif
