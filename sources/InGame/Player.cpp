#include "Player.h"


PlayerClass::PlayerClass() {

	PlayerGlobalId = -1;
	PlayerTeamId = -1;

	selectedHero = NULL;
	playerLeague = NULL;
}

int PlayerClass::SetName(char* name) {
	size_t size = strv.copy(playerName, 6,);
	return GE_RETURN_OK;
}