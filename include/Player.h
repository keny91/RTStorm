/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Player.h'			DESCRIPTION:
	
This file is dedicated to .


-----------------------------------------------------------------------------*/

#include "du.h"

// maybe use other classes as "external" resources, but define them here as a class

// extern class Character;  // <- good when we just want to set callback with this classes/structs
#include "Character.h"

class Player
{
private:
	//int nof_characters;
	DuArray characters_ingame; // also contains nof_characters
	Team * player_team;
	PlayerScore * player_score;
	
	PlayerStadistics player_stadistics;
	
	
	string player_name;
	
	bool silenced;
	bool AI_controlled;
	int League;  // create a structure?   league_id, league_name, league_value_mod?
	


protected:

public:

	
	Player();
	~Player();








}
