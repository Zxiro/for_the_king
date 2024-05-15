#include "Test.h"
#include "entities/entity/creature/Player.h"
#include "entities/item/equipment/weapon/WoodenSword.h"

int main()
{
	Player player({ 1,2 }, "1");

	WoodenSword weapon;
	player.wearWeapon(&weapon);
	player.getPAttack();

	//Test test;
	//test.printUI();
}
