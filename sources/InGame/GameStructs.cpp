
#include "GameStructs.h"

int modifierClass::applyModifier(int value, int *resulting_value)
{
	// the higher the modifier, the smaller the result 
	if (inverseProportional)
		*resulting_value = value - value * modValue;
	else 
		*resulting_value = value + value * modValue;
	return GE_RETURN_OK;
}

