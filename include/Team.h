#ifndef _TEAM_H_
#define _TEAM_H_

#include "du.h"
#include "Player.h"

//extern class GameClass * Game;
typedef class GameClass * Game;
extern enum TeamColor;
typedef class TeamClass 
{

public:
	
	TeamColor teamColor;
	DuList PlayerList;
	bool isFullTeam;
	TeamClass();
	~TeamClass();
	Game parentGame;


private:

	int nofMaxPlayers;
	int addPlayer(Player the_player);
	int setTeamColor(TeamColor color);
	int getParentGame(Game* game_reference);
	

}* Team;


#endif // _TEAM_H_