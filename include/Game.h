/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Game.h'			DESCRIPTION:
	
Storage of game event functions.

Ex: Death, score, ...

-----------------------------------------------------------------------------*/

#include "du.h"



class Game
{
	
public: 
	Game();
	~Game();
	
	int duration;   // In seconds / time?
	Score score_team_red;	// reference to score structure
	Score score_team_blue;
	
	Team team_red;	// Reference to team structure
	Team team_blue;
	
	Map the_map;
	
	Event * event_list; // tribute/tower/objective spawn


	// Functions
	
	int StartGame();
	// next probably goes in "ENGINE"
	int SetNextEventCallback(int timing, (void *) funct );  // New thread should trigger an event when the marked time comes.
	int InitializeKeyPressCallbacks();  // predefined function that compiles a bunch of ON-KEY-PRESS callbacks.  
	
	int 
	// Get/Set functions
	
	
private:


protected:

}


