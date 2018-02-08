/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Game.h'			DESCRIPTION:
	
Storage of game event functions.

Ex: Death, score, ...

-----------------------------------------------------------------------------*/

#include "du.h"
#include "Score.h"

extern class Team;

// all this is defined in score.h so it is not necessary
extern class ScoreCoreGame;
extern class ScorePointedGame;
extern class TeamScore;


// all these should be defined in RT.h
extern Struct RTData;
extern void RTSetNewGameEventCB(HostData * data); //host data 
extern void RTSetErrorOnProcessRTDataCB(int error_id, string error_msg); //host data


// depending on which map, the game will init different params on creation
extern enum MapPool {Cursed_Hollow, Blackhearts_Bay, Garden_of_Terror,Towers_of_Doom, Sky_Temple, Volskaya_Foundry,/
	Tomb_of_Spiderqueen, Haunted_Mines, Hanamura, Battlefield_of Eternity, Punishers, Braxis_Holdout, Warhead_Junktion};
// each of the above should have an individual

// win condition -> enemy points reach 0
extern enum Map_Score_Based {Towers_of_Doom, Hanamura};
// condition could still be Destroy core, but core only can TakeDamage() through objectives.



// re-naming some objects to more intuitive 
typedef int effecttype;

class Game
{
	
public: 
	Game();
	// just an internal call to Game(), and player and map linkage.
	static void CreateGame(Map the_Map, Team teamA, Team teamB, Game* game_empty_ptr_ref); 
	~Game();

protected:
	int duration;   // In seconds / time?
	TeamScore score_team_red;	// reference to score structure
	TeamScore score_team_blue;
	
	Team team_red;	// Reference to team structure
	Team team_blue;
	
	Map the_map;
	
	Event * event_list; // tribute/tower/objective spawn


	// Functions
	
	int StartGame();
	// next probably goes in "ENGINE"
	int SetNextEventCallback(int timing, (void *) funct );  // New thread should trigger an event when the marked time comes.
	int InitializeKeyPressCallbacks();  // predefined function that compiles a bunch of ON-KEY-PRESS callbacks.  
	int InitHostEngine();
	
	// Get/Set functions
	
	
private:


};





class Effect {
public:
	// Effect(); this is the root/parent class

	effecttype type;	
	int hasValidValue();
		;
protected:
	;
private:
	;
};
