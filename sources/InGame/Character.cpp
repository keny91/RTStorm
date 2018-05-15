
#include "Character.h"


/*****	Start of CharacterClass Definition	*****/

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

/*****	End of CharacterClass Definition	*****/


/*****	Start of CharacterStatusStruct Definition	*****/
bool CharacterStatusStruct::isActiveStatus(double* currentTime, StatusLabel status) 
{
	int rc;
	Status theStatus;
	rc = getStatus(status, &theStatus);
	if (rc != GE_RETURN_OK) 
	{
		return rc;
	}

	if (theStatus->isActive)
	{
		*currentTime = theStatus->duration;
		return theStatus->isActive;
	}
	else {
		*currentTime = -1;
		return theStatus->isActive;
	}

}


int CharacterStatusStruct::getStatus(StatusLabel status, Status* theStatusRef) {
	switch (status)
	{
	case Stunned:
		*theStatusRef = StunnedStatus;
		return GE_RETURN_OK;
			break;
	case Slowed:
		*theStatusRef = SlowedStatus;
		return GE_RETURN_OK;
		break;
	case Rooted:
		*theStatusRef = RootedStatus;
		return GE_RETURN_OK;
		break;
	case Dazed:
		*theStatusRef = DazedStatus;
		return GE_RETURN_OK;
		break;
	case Unstopable:
		*theStatusRef = UnstopableStatus;
		return GE_RETURN_OK;
		break;
	case Protected:
		*theStatusRef = ProtectedStatus;
		return GE_RETURN_OK;
		break;
	case PhysicalProtected:
		*theStatusRef = PhysicalProtectedStatus;
		return GE_RETURN_OK;
		break;
	case MagicProtected:
		*theStatusRef = MagicProtectedStatus;
		return GE_RETURN_OK;
		break;
	case Blinded:
		*theStatusRef = BlindedStatus;
		return GE_RETURN_OK;
		break;
	case Stopped:
		*theStatusRef = StoppedStatus;
		return GE_RETURN_OK;
		break;
	default:
		*theStatusRef = NULL;
		return GE_RETURN_UNKNOWN_TYPE;
		break;
	}
}


/*****	End of CharacterClass Definition	*****/