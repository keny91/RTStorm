
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


int BarClass::modifyMaxValue(int value) 
{
	maxBarValue = value;
	return GE_RETURN_OK;
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


int BarClass::getPercentageMissing(int * perc_val_ref)
{
	*perc_val_ref = getPercentageFilled(perc_val_ref);
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


int BarClass::getAmountByPercentage(int  perc_val, int *ret_val) 
{
	int tmp;

	if (perc_val > 100 || perc_val < 0)
		return GE_RETURN_INVALID_INPUT;

	*ret_val = maxBarValue * perc_val / 100; // 

	return GE_RETURN_OK;
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

/*****	End of BarClass Definition	*****/

/*****	Start of HealthBarClass Definition	*****/

// this should be declared in whatever is going to contain the healthbar
HealthBarClass::HealthBarClass(int base_armor, Character character_reference)
{
	armor = new ArmorClass(base_armor);  // create
	armor->setHealthBarRef((void*)this);  // link to parent

	healingModifier = new HealingModifierClass(); // similar to armor
	healingModifier->setParent((void*)this);	// link

	setParent(character_reference);  // link with character
}


int HealthBarClass::getParent(void* ref)
{
	// our armorClass ref is passed as a generic void*
	ref = characaterParentRef;
}

int HealthBarClass::setParent(void* ref)
{

	characaterParentRef = (Character)ref;
	// check if it worked and we can properly read the structure
	// property accesible
	if (characaterParentRef)
		return GE_RETURN_OK;
	else
	{
		return GE_RETURN_INVALID_REF_TYPE;
	}
}

int HealthBarClass::getHealthAmountByPercentage(int  perc_val, int *ret_val) 
{
	int rc;
	rc = getAmountByPercentage( perc_val, ret_val); //call to inherited funct
	return rc;
}

int HealthBarClass::getHealthPercentageMissing(int * perc_val_ref) 
{
	int rc;
	rc = getPercentageMissing(perc_val_ref); //call to inherited funct
	return rc;
}


int HealthBarClass::getPercentageFilled(int * perc_val_ref)
{
	int rc;
	rc = getPercentageFilled(perc_val_ref); //call to inherited funct
	return rc;
}
HealthBarClass::~HealthBarClass()
{
	delete(armor);
	delete(healingModifier);
}


int HealthBarClass::takeDamage(int value, DamageType dmg_type)
{
	int rc;
	int dmg_value;

	// only positive values
	if (value <= 0)
		return GE_RETURN_INVALID_INPUT;

	//is mitigation applied
	dmg_value = armor->takeDamage(value, dmg_type);
	rc = modifyValue(dmg_value);

	return rc;
}


int HealthBarClass::healDamage(int value)
{
	int rc;
	int dmg_value;

	// only positive values
	if (value <= 0)
		return GE_RETURN_INVALID_INPUT;

	dmg_value = healingModifier->calculateHeal(value);
	rc = modifyValue(value);

	return rc;
}

/*****	End of HealthBarClass Definition	*****/


/*****	Start of ManaBarClass Definition	*****/

/* Value can be either positive or negative */

ManaBarClass::ManaBarClass() 
{

	currentBarValue = 0;
}

ManaBarClass::ManaBarClass(int maxVal)
{
	maxBarValue = maxVal;
	currentBarValue = 0;
}

int ManaBarClass::modifyMana(int value) 
{

	modifyValue(value);
	return GE_RETURN_OK;
}


int ManaBarClass::getParent(void* ref)
{
	// our armorClass ref is passed as a generic void*
	ref = characaterParentRef;
}


//int ManaBarClass::getPercentageFilled(int * perc_val_ref)
//{
//	int rc;
//	rc = getPercentageFilled(perc_val_ref); //call to inherited funct
//	return rc;
//}


int ManaBarClass::getManaAmountByPercentage(int  perc_val, int *ret_val)
{
	int rc;
	rc = getAmountByPercentage(perc_val, ret_val); //call to inherited funct
	return rc;
}

int ManaBarClass::getManaPercentageMissing(int * perc_val_ref)
{
	int rc;
	rc = getPercentageMissing(perc_val_ref); //call to inherited funct
	return rc;
}

int ManaBarClass::setParent(void** ref)
{

	characaterParentRef = (HeroCharacter)*ref;
	// check if it worked and we can properly read the structure
	// property accesible
	if (characaterParentRef)
		return GE_RETURN_OK;
	else
	{
		return GE_RETURN_INVALID_REF_TYPE;
	}
}

/*****	End of ManaBarClass Definition	*****/



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
