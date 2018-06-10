#include "Team.h"

int TeamClass::addPlayer(Player the_player) {


	// Don´t link player if team is full
	if (isFullTeam) {
		return GE_RETURN_TEAM_FULL;
	}

	// Just need to initialize
	
	if (!playerList[curr_nof_players])
		return GE_RETURN_ALREADY_INITIALIZED;

	the_player->PlayerTeamId = curr_nof_players + 1;
	the_player->parentTeamRef = (void*) this;

	playerList[curr_nof_players] = the_player; // assign memory address to

	return GE_RETURN_OK;
}


TeamClass::TeamClass(int max_players)
{
	//int size = sizeof(PlayerClass);
	nof_max_players = max_players;
	curr_nof_players = 0;
	//PlayerList = new Player[max_players];
	
}

TeamClass::TeamClass()
{
	//int size = sizeof(PlayerClass);
	nof_max_players = DEFAULT_NOF_PLAYERS;
	curr_nof_players = 0;
	/*PlayerList = new Player[DEFAULT_NOF_PLAYERS];*/

}