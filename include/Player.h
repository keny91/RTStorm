/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Player.h'			DESCRIPTION:
	
This file is dedicated to .


-----------------------------------------------------------------------------*/


using namespace std;
#include "du.h"
#include "Hero.h"
#include <string>

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
	string player_name;
	int PlayerGlobalId;
	Team playerTeam;  // reference to the team the player belongs to
	PlayerScore player_score;	// reference to score
	PlayerStadistics player_stadistics;  // ...
	Rank playerLeague; 
	Hero selectedHero;   // stat info, char reference, talentable
	DuList charactersInGame;   // characters might change, or be multiple
	
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
	PlayerClass();
	~PlayerClass();


private:
	int AddCharacter(Character theCharacter); // can be done multiple times, this will add a character 
	int AddPlayerScore(PlayerScore thePlayerScore);
	int AddLeague(PlayerScore thePlayerScore);
	int SetName(string Name);
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
