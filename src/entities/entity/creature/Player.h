#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "../../item/equipment/accessory/Accessory.h"
#include "../../item/equipment/armor/Armor.h"
#include "../../item/equipment/weapon/Weapon.h"
#include <random>
#include <cmath>
#include "../../../manager/Singleton.h"
#include "../../../exception/FocusNotEnoughException.h"
#include "../../../utils/EffectUtil.h"
#include "../../../enum/InteractiveType.h"
#include "../../../manager/BackpackManager.h"


class Player : public Creature
{
public:
	Player(const Position& _position, const std::string& _display) : Creature(_position, _display)
	{
	}

	// 行動順序(Priority)
	int getPriority() const
	{
		return std::floor(this->totalMovementCount / getSpeed()) * 100;
	}

	//在移動前，根據Stat::Speed決定可以投擲多少個骰子，骰子的數量就是 MaxMovementPoint
	int getMaxMovementPoint() const
	{
		return std::floor(getSpeed() / 10);
	}

	//每回合通過投擲骰子的成功數量，決定可以移動幾個Rect的數值
	int getMovementPoint(int useFocusCount = 0)
	{
		this->currentMovementCount = 0;
		int maxPoint = getMaxMovementPoint();
		int successPoint = 0;
		int focusCount = useFocusCount;
		for (int i = 0; i < maxPoint; i++)
		{
			if (focusCount > 0)
			{
				focusCount -= 1;
				successPoint += 1;
				decreaseFocus();
				continue;
			}


			double chance = getRollDiceChance();
			if (!isRollDiceSuccess(chance))
			{
				continue;
			}

			successPoint += 1;
		}

		return successPoint;
	}

	// 角色移動後需要呼叫此function來記錄移動次數
	void increaseMovementCount()
	{
		this->currentMovementCount = 0;
		this->totalMovementCount += 1;
	}

	// 取得角色從骰完骰子後移動了幾步
	int getMovementCount()
	{
		return this->currentMovementCount;
	}

	//互動機制(Interactive) 擲骰子
	void execInteractive(InteractiveType type, int useFocus = 0)
	{
		int rollDiceCount = 0;
		int successCount = 0;
		int focusCount = useFocus;
		double rollDiceChance = 0;

		auto success = [&]()
		{
			if (type == InteractiveType::treasure)
			{
				int amount = successCount * 2;
				Singleton<BackpackManager>::instance().addMoney(amount);
			}
		};

		auto failed = [&]()
		{
			if (type == InteractiveType::treasure)
			{
				int calcVitality = this->vitality - std::floor(this->vitality * 0.1);
				this->setVitality(calcVitality);
			}
		};

		if (type == InteractiveType::treasure)
		{
			rollDiceCount = 3;
			rollDiceChance = 0.5;
			for (int i = 0; i < rollDiceCount; i++)
			{
				if (focusCount > 0)
				{
					focusCount -= 1;
					successCount += 1;
					decreaseFocus();
					continue;
				}

				if (!isRollDiceSuccess(rollDiceChance))
				{
					continue;
				}

				successCount += 1;
			}
		}

		if (successCount == 0)
		{
			failed();
			return;
		}

		success();
	}

	//Equip function
	void wearWeapon(Weapon* weapon)
	{
		this->weapon = weapon;
	}

	void wearArmor(Armor* armor)
	{
		this->armor = armor;
	}

	void wearAccessory(Accessory* accessory)
	{
		this->accessory = accessory;
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

	Weapon* getWeapon()
	{
		return this->weapon;
	}

	Armor* getArmor()
	{
		return this->armor;
	}

	Accessory* getAccessory()
	{
		return this->accessory;
	}


	// getter setter
	double getVitality() const override
	{
		return vitality;
	}

	double getFocus() const override
	{
		int effect = EffectUtil<Weapon>::getFocus(this->weapon);
		effect += EffectUtil<Armor>::getFocus(this->armor);
		effect += EffectUtil<Accessory>::getFocus(this->accessory);
		return focus + effect;
	}

	double getSpeed() const override
	{
		int effect = EffectUtil<Weapon>::getSpeed(this->weapon);
		effect += EffectUtil<Armor>::getSpeed(this->armor);
		effect += EffectUtil<Accessory>::getSpeed(this->accessory);
		return speed + effect;
	}

	double getHitRate() const override
	{
		int effect = EffectUtil<Weapon>::getHitRate(this->weapon);
		effect += EffectUtil<Armor>::getHitRate(this->armor);
		effect += EffectUtil<Accessory>::getHitRate(this->accessory);
		return hitRate + effect;
	}

	double getPAttack() const override
	{
		int effect = EffectUtil<Weapon>::getPAttack(this->weapon);
		effect += EffectUtil<Armor>::getPAttack(this->armor);
		effect += EffectUtil<Accessory>::getPAttack(this->accessory);
		return pAttack + effect;
	}

	double getMAttack() const override
	{
		int effect = EffectUtil<Weapon>::getMAttack(this->weapon);
		effect += EffectUtil<Armor>::getMAttack(this->armor);
		effect += EffectUtil<Accessory>::getMAttack(this->accessory);
		return mAttack + effect;
	}

	double getPDefense() const override
	{
		int effect = EffectUtil<Weapon>::getPDefense(this->weapon);
		effect += EffectUtil<Armor>::getPDefense(this->armor);

		int accessoryPDefense = EffectUtil<Accessory>::getPDefense(this->accessory);
		int res = 0;
		// 特別處理，寫法很差，目前想不到更好的寫法
		if (accessory != nullptr && accessory->getName() == "LaurelWreath")
		{
			res = (pDefense + effect) * accessoryPDefense;
		}
		else
		{
			effect += accessoryPDefense;
			res = pDefense + effect + accessoryPDefense;
		}

		return res;
	}

	double getMDefense() const override
	{
		int effect = EffectUtil<Weapon>::getMDefense(this->weapon);
		effect += EffectUtil<Armor>::getMDefense(this->armor);
		effect += EffectUtil<Accessory>::getMDefense(this->accessory);
		return mDefense + effect;
	}

	bool isPassable() const override
	{
		return true; // Players are passable
	}

	void setVitality(int vit)
	{
		vitality = vit;
	}

	void setAttack(int atk)
	{
		pAttack = atk;
	}

	void setPDefense(int def)
	{
		pDefense = def;
	}

	void setMDefense(int def)
	{
		mDefense = def;
	}

private:
	Weapon* weapon = nullptr;
	Armor* armor = nullptr;
	Accessory* accessory = nullptr;
	int totalMovementCount = 0;
	int currentMovementCount = 0;
	int maxMovement = 0;

	bool isRollDiceSuccess(double chance) const
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(chance);
		return d(gen);
	}

	double getRollDiceChance() const
	{
		return getSpeed() / 10;
	}

	void decreaseFocus()
	{
		if (this->focus == 0)
		{
			throw FocusNotEnoughException();
		}
		this->focus -= 1;
	}
};

#endif