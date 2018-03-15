
#include "Bar.h"



/*****	Start of BarClass Definition	*****/


bool BarClass::checkEmpty() 
{
	if (currentBarValue <= 0)
		return true;
	else
		false;
}


/**		Function:	modifyValue(int value)
	Adds the value to the
*/
int BarClass::modifyValue(int value)
{
	int calculatedValue;

	calculatedValue = currentBarValue + value;

	if (calculatedValue <= 0) 
	{
		currentBarValue = 0;
		return BAR_REACHED_EMPTY;
	}
	else if (calculatedValue >= maxBarValue)
	{
		currentBarValue = maxBarValue;
		return BAR_REACHED_MAX;
	}
	else
		currentBarValue = calculatedValue;

	return BAR_ALL_GOOD;
}


int BarClass::modifyValue(int value, int * excess)
{
	int calculatedValue;
	*excess = 0;

	calculatedValue = currentBarValue + value;

	if (calculatedValue <= 0)
	{
		*excess = calculatedValue;
		currentBarValue = 0;
		return BAR_REACHED_EMPTY;
	}
	else if (calculatedValue >= maxBarValue)
	{
		*excess = calculatedValue;
		currentBarValue = maxBarValue;
		return BAR_REACHED_MAX;
	}
	else
		currentBarValue = calculatedValue;

	return BAR_ALL_GOOD;
}


int BarClass::getPercentageFilled(int * perc_val_ref) 
{
	*perc_val_ref = int(currentBarValue * 100 / maxBarValue);
	return GE_RETURN_OK;
}

bool BarClass::isAboveTH(int perc_th)
{
	int percent_value;
	getPercentageFilled(&percent_value);
	if (percent_value > perc_th)
		return true;
	else
		return false;
}

bool BarClass::isBelowTH(int perc_th)
{
	int percent_value;
	getPercentageFilled(&percent_value);
	if (percent_value < perc_th)
		return true;
	else
		return false;
}

/*****	Start of BarClass Definition	*****/

/*****	Start of HealthBarClass Definition	*****/

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
