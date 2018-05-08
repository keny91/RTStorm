#include "Character.h"

/***	CharacterClass	***/
int CharacterClass::SetMaxHP(int value) 
{
	healthBar->modifyMaxValue(value);
	return GE_RETURN_OK;
}



/*** HeroCharacterClass	***/

int HeroCharacterClass::SetMaxEnergybar(int value)
{

	ResourceBar->SetMaxValue(value);
	return GE_RETURN_OK;
}



/** EnergySourceStruct	**/
int EnergySourceStruct::SetMaxValue(int maxValue)
{


	return GE_RETURN_OK;
}



EnergySourceStruct::EnergySourceStruct(int maxValue, ResourceBarTypes type, HeroCharacter characaterParentRef)
{

	switch (type)
	{
	case mana:
		//theBar = (energyRef) (new ManaBarClass(maxValue));
		ManaBar bar_ref = new ManaBarClass(maxValue);
		bar_ref = setParent(void** ref);
		break;
	case none:
		break;
	case energy:
		break;
	case rage:
		break;
	case ow_ulti:
		break;
	case other:
		break;
	default:
		break;
	}

}