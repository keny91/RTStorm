//#include "stdafx.h"
#include "Armor.h"


/*** ARMOR******/


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






ArmorClass::~ArmorClass()
{
}



/*** ARMOR_MODIFIER******/

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

	// Don´t Allow the modValue to go beyond constrains
	if (modValue > maxCap)
		modValue = maxCap;
	else if (modValue < minCap)
		modValue = minCap;
	return modValue;
}


/*** PHYSICAL_ARMOR******/
 PhysicalArmorClass::PhysicalArmorClass()
{

}



 /*** MAGIC_ARMOR******/
 MagicArmorClass::MagicArmorClass()
 {

 }


