
#include "GameStructs.h"


/*****	Start of modifierClass Definition	*****/

int modifierClass::applyModifier(int value)
{
	int resulting_value;
	// the higher the modifier, the smaller the result 
	if (inverseProportional)
		resulting_value = value - value * modValue;
	else 
		resulting_value = value + value * modValue;
	return resulting_value;
}



int modifierClass::modifyValue(int amount) 
{
	modValue += amount;
	return GE_RETURN_OK;
}


/*****	End of modifierClass Definition	*****/


/*****	Start of modifierClass Definition	*****/

/*****	End of modifierClass Definition	*****/