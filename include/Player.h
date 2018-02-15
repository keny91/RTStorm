/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Player.h'			DESCRIPTION:
	
This file is dedicated to .


-----------------------------------------------------------------------------*/

#include "du.h"

// maybe use other classes as "external" resources, but define them here as a class 
// ANSWER: NO!, extern only is used for communication between engines.

// extern class Character;  // <- good when we just want to set callback with this classes/structs
#include "Character.h"

/*  these structs are type-defined in their respective class declaration docs
typedef _PlayerStadisticsClass * PlayerStadistics;
typedef _PlayerScoreClass * PlayerScore;
typedef _CharacterClass * Character;

*/



enum PlayerAtribute{Silenced, Player_Score, AI_Controlled,  } ;


typedef class _PlayerClass
{
private:
	//

	


protected:	
	string player_name;
	
	Team * player_team;  // reference to the team the player belongs to
	PlayerScore player_score;	
	PlayerStadistics player_stadistics;  // 
	League playerLeague; 
	
	//int nof_characters;
	DuArray characters_ingame; // also contains nof_characters
	
	bool silenced;
	bool AI_controlled;
	 // create a structure?   league_id, league_name, league_value_mod?
	int CreatePlayer(Player emptyPlayerReference);
	
	// functions
	// functions called from team/game creation (AKA init())
	
	int SetPlayerAttribute(PlayerAtribute theAttribute, void* value);  // way to call private functions after validating the value
			          					   // casting void* to the approviate reference value
	
public:

	// protected?
	Player();
	~Player();


private:
	int AddCharacter(Character theCharacter); // can be done multiple times, this will add a character 
	int AddPlayerScore(PlayerScore thePlayerScore);
	int AddLeague(PlayerScore thePlayerScore);



} PlayerClass, * Player;



// NOTE-> CREATE A SIMILAR DOCUMENT FOR THE LEAGUE CLASS  --  league.h
// should these be static?/ non-visible outside this class?
typedef enum Leagues{bronze,silver,golg,platinum,diamond,master,grandmaster} PlayerLeague;
typedef enum LeagueDivision{I,II,III,IV,V} PlayerDivision;
typedef enum LeagueDivision{I,II,III,IV,V} PlayerDivision;

typedef class _LeagueClass
{
	
	protected:
		int GetNumericRank();
		int CreateLeague(League emptyLeagueReference);
	private:
		playerleague league;
		PlayerDivision division;
		int MMR;  // should all mmrs be displayed?
		int NumericRank;
	
	
		_LeagueClass();
		~_LeagueClass();
		int DetermineInternalNumericRank();
	
		
} LeagueClass, *League;
