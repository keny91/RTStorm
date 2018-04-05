//#include "stdafx.h"
#include "Armor.h"




/*****	Start of ArmorClass Definition	*****/

ArmorClass::ArmorClass()
{
	currentArmorValue = 0;
	baseArmorValue = 0;
	minArmorCap = MIN_ARMOR_CAP;  /* Regular armor goes from a min -30 to a max of 75 (% based) */
	maxArmorCap = MAX_ARMOR_CAP;

	// create nested objects
	magicArmor = new MagicArmorClass();
	physicalArmor = new PhysicalArmorClass();

	// would this work?
	// get the objects a reference
	magicArmor->setParent((void*)this);
	physicalArmor->setParent((void*)this);
}


ArmorClass::ArmorClass(int base_value)
{
	currentArmorValue = base_value;
	baseArmorValue = base_value;
	minArmorCap = MIN_ARMOR_CAP;  /* Regular armor goes from a min -30 to a max of 75 (% based) */
	maxArmorCap = MAX_ARMOR_CAP;

	// create nested objects
	magicArmor = new MagicArmorClass();
	physicalArmor = new PhysicalArmorClass();

	// would this work?
	// get the objects a reference
	magicArmor->setParent((void*)this);
	physicalArmor->setParent((void*)this);
}


bool ArmorClass::checkValidArmor() 
{
	// maybe some additional check is needed
	if (minArmorCap > -HUNDRED_PERC_VAL && maxArmorCap < HUNDRED_PERC_VAL)
		return TRUE;
	else
		return FALSE;
}


int ArmorClass::getHealthBarRef(void * health_Ref)
{
	health_Ref = (void*)parentHealthRef;
	return GE_RETURN_OK;
}


int ArmorClass::setHealthBarRef(void * health_Ref)
{
	parentHealthRef = (HealthBar)health_Ref;
	return GE_RETURN_OK;
}

int ArmorClass::addPermanentArmor(ArmorType type, int value) 
{
	switch (type)
	{

		// add both
	case FullArmor:
		baseValue = value;
		magicArmor->setPermanentArmor(value);
		physicalArmor->setPermanentArmor(value);
		break;
		
	case Magical:
		magicArmor->setPermanentArmor(value);
		break;

	case Physical:
		physicalArmor->setPermanentArmor(value);
		break;

	default:
		// error? invalid armortype
		break;
	}
}



int ArmorClass::modifyArmor(ArmorType type, int value)
{
	switch (type)
	{

		// add both
	case FullArmor:
		currentArmorValue = value;
		magicArmor->modifyValue(value);
		physicalArmor->modifyValue(value);
		break;

	case Magical:
		magicArmor->modifyValue(value);
		break;

	case Physical:
		physicalArmor->modifyValue(value);
		break;

	default:
		// error? invalid armortype
		break;
	}
}

int ArmorClass::takeDamage(int damage, DamageType dmg_type) 
{
	int result_dmg;
	switch (dmg_type)
	{
		//TrueDamage, PhysicalDamage, MagicDamage, PercentDamege
		// add both
	case TrueDamage:
		// ignores armor
		result_dmg = damage;
		break;

	case MagicDamage:
		result_dmg = magicArmor->calculateDamage(damage);
		break;

	case PhysicalDamage:
		result_dmg = physicalArmor->calculateDamage(damage);
		break;

	case PercentDamege:
		// ignores armor
		// NEED PERCENTAGE CALCULATOR... better the amount should be got before
		parentHealthRef->
		// damage will be the resulting dmg number
		// no armor check required
		result_dmg = damage;
		break;

	default:
		// error? invalid armortype
		break;
	}



}


ArmorClass::~ArmorClass()
{
}

/*****	End of ArmorClass Definition	*****/


/*****	Start of ArmorModifierClass Definition	*****/


int ArmorModifierClass::getParent(void* ref)
{
	// our armorClass ref is passed as a generic void*
	ref = armorParentRef;
}

int ArmorModifierClass::setParent(void* ref)
{

	armorParentRef = (Armor)ref;
	// check if it worked and we can properly read the structure
	// property accesible
	if (armorParentRef->checkValidArmor())
		return GE_RETURN_OK;
	else
	{
		return GE_RETURN_INVALID_REF_TYPE;
	}



}

//implemented as modifier not armor modifier
//int ArmorModifierClass::applyModifier(int value, int *resulting_value) 
//{
//	// the higher the modifier, the smaller the result 
//	if (inverseProportional)
//		*resulting_value = value + value *
//
//	return 1;
//
//}


int ArmorModifierClass::modifyValue(int amount)
{
	modValue += amount;

	// Don�t Allow the modValue to go beyond constrains
	if (modValue > maxCap)
		modValue = maxCap;
	else if (modValue < minCap)
		modValue = minCap;
	return modValue;
}




int ArmorModifierClass::calculateDamage(int damage)
{
	int resultingDamage;
	//Armor parentRef;
	//getParent((void*)parentRef);  // get
	//parentRef = (Armor)parentRef; // cast
	resultingDamage = applyModifier(damage);

	return resultingDamage;
}


int ArmorModifierClass::getParent(void* ArmorRef)
{	
	ArmorRef = (void*)armorParentRef;
	return GE_RETURN_OK;
}

int ArmorModifierClass::setParent(void* ref)
{
	armorParentRef = (Armor)ref;
	return GE_RETURN_OK;
}

int ArmorModifierClass::setPermanentArmor(int value)
{
	if (value <= maxCap && value >= minCap)
		baseValue = value;
	else
		return GE_RETURN_INVALID_INPUT;

	return GE_RETURN_OK;
}

/*****	End of ArmorModifierClass Definition	*****/





/*****	Start of PhysicalArmorClass Definition	*****/
 PhysicalArmorClass::PhysicalArmorClass()
{
	 inverseProportional = TRUE;
	 modValue = 0;
	 maxCap = 75;
	 minCap = -30;
}



 /*****	End of PhysicalArmorClass Definition	*****/

 /*****	Start of MagicArmorClass Definition	*****/
 MagicArmorClass::MagicArmorClass()
 {
	 baseValue = 0;
	 inverseProportional = TRUE;
	 modValue = baseValue;
	 maxCap = 75;
	 minCap = -30;
 }


 /*****	End of MagicArmorClass Definition	*****/



 /*****	Start of Healing Modifier Definition	*****/
 int HealingModifierClass::getParent(void* health_Bar_Ref)
 {
	 health_Bar_Ref = (void*)healthBarRef;
	 return GE_RETURN_OK;
 }

 int HealingModifierClass::setParent(void* health_Bar_Ref)
 {
	 healthBarRef = (HealthBar)health_Bar_Ref;
	 return GE_RETURN_OK;
 }

 int HealingModifierClass::calculateHealing(int healing) 
 {
	 int result;
	 result = modValue * healing + healing;
	 return result;
 }


 HealingModifierClass::HealingModifierClass()
 {
	 inverseProportional = FALSE;
	 maxCap = -100;
	 minCap = 100;
	 baseValue = 0;
	 modValue = baseValue;
	 
 }

 /***** End	Healing Modifier Definition	*****/