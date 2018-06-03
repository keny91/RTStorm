#ifndef _CORE_CONTROL_H_
#define _CORE_CONTROL_H_ 

#include <string>
#include "Hero.h"

using namespace std;

// Defined at "Hero.h"
extern enum heroName;

//#using namespace std;

/*	Create a match object	*/
int InitStandardMatch();

extern class PlayerClas;
extern class TeamClass;


typedef class MatchClass {
	int currentPlayers;
	
	// teams include the references to heroes.
	Team BlueTeam;
	Team RedTeam;

	/*	Create a player that is playing with a hero (inserted as param)*/
	int InitPlayer(Player* thePlayer,string PlayerName, heroName theHero);



}* Match;




#endif