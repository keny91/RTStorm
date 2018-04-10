
#include "Character.h"

int CharacterClass::setParentHero(void * ref) 
{
	heroParentRef = (Hero)ref;
	return GE_RETURN_OK;
}

int CharacterClass::getParentHero(void * hero_ref)
{
	hero_ref = (void*)heroParentRef;
	return GE_RETURN_OK;
}
