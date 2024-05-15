#ifndef EFFECT_UTIL_H
#define EFFECT_UTIL_H
#include "../entities/item/equipment/Equipment.h"

template<class T>
class EffectUtil
{
public:
	template<class T = Equipment>

	static int getSpeedEffect(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}
	
		return equip->getEffect().speedEffect;
	}

	static int getFocus(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().focusEffect;
	}

	static int getSpeed(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().speedEffect;
	}

	static int getHitRate(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().hitRateEffect;
	}

	static int getPAttack(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().pAttackEffect;
	}

	static int getMAttack(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().mAttackEffect;
	}

	static int getPDefense(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().pDefenseEffect;
	}

	static int getMDefense(T* equip)
	{
		if (equip == nullptr)
		{
			return 0;
		}

		return equip->getEffect().mDefenseEffect;
	}
};

#endif