/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Player.h'			DESCRIPTION:
	
This file is dedicated to .


-----------------------------------------------------------------------------*/


#include "du.h"
#include "Hero.h"
#include <string>
#include "GE_MSGs.h"
#include <stdio.h>
#include <string.h>


using namespace std;

/*  these structs are type-defined in their respective class declaration docs
typedef _PlayerStadisticsClass * PlayerStadistics;
typedef _PlayerScoreClass * PlayerScore;
typedef _CharacterClass * Character;

*/


// maybe we need a better system than an enum
enum PlayerAtribute{Silenced, Player_Score, AI_Controlled, ... } ;


typedef class PlayerClass
{
private:
	//

	


protected:	

	
	PlayerScore player_score;	// reference to score
	PlayerStadistics player_stadistics;  // ...
	Rank playerLeague; 
	Hero selectedHero;   // stat info, char reference, talentable
	DuList charactersInGame;   // characters might change, or be multiple
	bool PlayerInitialized = false;
	//int nof_characters;  // contained in dulist

	
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
	int PlayerGlobalId;
	int PlayerTeamId;
	char* playerName;
	PlayerClass();
	~PlayerClass();
	void* parentTeamRef;  // reference to the team the player belongs to

private:
	int AddCharacter(Character theCharacter); // can be done multiple times, this will add a character 
	int AddPlayerScore(PlayerScore thePlayerScore);
	int AddLeague(PlayerScore thePlayerScore);
	int SetName(char* Name);
	int SetHero(Hero picked_hero); // set hero and initialize characters
	int AddPlayerStadistics(PlayerStadistics Stadistics)


} * Player;



// NOTE-> CREATE A SIMILAR DOCUMENT FOR THE LEAGUE CLASS  --  league.h
// should these be static?/ non-visible outside this class?
typedef enum Leagues{bronze,silver,golg,platinum,diamond,master,grandmaster} PlayerLeague;
typedef enum Divisions{I,II,III,IV,V} PlayerDivision;

typedef class RankClass
{
	
	protected:
		int GetNumericRank();
		int CreateLeague(League emptyLeagueReference);
	private:
		PlayerLeague league;
		PlayerDivision division;
		int MMR;  // should all mmrs be displayed?
		int NumericRank;
	
	
		LeagueClass();
		~LeagueClass();
		int DetermineInternalNumericRank();
	
		
} *Rank;
