
#include "Bar.h"


BarClass::

// this should be declared in whatever is going to contain the healthbar
HealthBarClass::HealthBarClass(int base_armor, Character character_reference)
{
	armor = new ArmorClass(base_armor);
	//CreateArmor(&armor, base_armor);
	healingModifier = new HealingModifierClass(); // similar to armor

	setParent(character_reference);  // link with character
}

//int HealthBarClass::CreateHealthBar()


HealthBarClass::~HealthBarClass()
{
	delete(armor);
	delete(healingModifier);
}


int ManaBarClass::modifyMana(int value) 
{

	modifyValue(value);
	return GE_RETURN_OK;
}


//// NOT CORRECT -> Must set all armors (armor, mArmor, pArmor)
//int HealthBarClass::CreateArmor(Armor* armorEmptyRef, int base_value = 0)
//{
//	// reference must be empty
//	if (armorEmptyRef)
//		return GE_RETURN_NON_EMPTY_REF;
//
//	// the value must be valid
//	if (base_value < MIN_ARMOR_CAP || MAX_ARMOR_CAP < base_value)
//		return GE_RETURN_INVALID_INPUT;
//
//	// default armor
//	if (base_value == 0)
//		*armorEmptyRef = new ArmorClass();
//	// armor with custom base value
//	else
//		*armorEmptyRef = new ArmorClass(base_value);
//
//
//	*ar
//
//	// we run out of memory
//	if (!*armorEmptyRef)
//		return GE_RETURN_OUT_OF_MEMORY;
//
//	return GE_RETURN_OK;
//}
