#ifndef _TEAM_H_
#define _TEAM_H_

#include "du.h"
#include "Player.h"
#include "GE_MSGs.h"
#include <cstdlib>
#include <iostream>


#define DEFAULT_NOF_PLAYERS 5


using namespace std;
//extern class GameClass * Game;
//typedef class GameClass * Game;
//extern enum TeamColor;

typedef class TeamClass 
{

public:
	
	//TeamColor teamColor;
	//DuList PlayerList;
	int nof_max_players;
	int curr_nof_players;

	Player * playerList;
	bool isFullTeam;

	TeamClass(int max_players);
	TeamClass()
	~TeamClass();
	//Game parentGame;
	int addPlayer(Player the_player);

private:

	int nofMaxPlayers;
	
	//int setTeamColor(TeamColor color);
	int getParentGame(Game* game_reference);
	

}* Team;


#endif // _TEAM_H_