/******** RT ANALYSIS API FOR HEROES OF THE STORM *********/

/** Version 0.1 - Development build	***/

/** DESCRIPTION

This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).

These first interaction is designed to analyze RT results in a recorded match replay.
The program is currently optimize to capture 5v5 matches of any kind since the UI 
shares a common design. Replays can be accelerated so the match does not need to 
be run at normal speed. However it might be important to specify such speed (although
later interactions of the program will try to detect the match speed automatically)

Ideally it is planned to replace heroes map icons with more easily recognized
QR codes for each of the players. Early versions will not support the multi/dual 
controlled heroes such as "Cho-gall" (2 playes, 1 character) or "the Lost Vikings"
(1 player - 3 characters).


The applications will be powered by a computer vision engine based on OpenCV 3.3
It will be interesting to include a KNN or NN to do some character/portrait recognition.


*/

#define RETURN_MSG_OK 1
#define RETURN_ERROR_NULL_POINTER 2
#define RETURN_ERROR_EMPTY_STRUCTURE 3
#define RETURN_UNDEFINED_ERROR 4
#define RETURN_BLABLBALA 5



protected class Score
{
	Team TeamA;
	Team TeamB;
	bool

};

struct Default_Team{
	Player Player1;
	Player Player2;
	Player Player3;
	Player Player4;
	Player Player5;
	Structures_Up;

};

class Team {

	Team();
	~Team();
	Player**players; // Array of players
	int Nof_players;
	bool all_assinged
}

int CreateTeam(int Nof_players);
int CreateDefaultTeam();  // Allocates and creates a 5 man team.
int CheckFullTeam(); // set internal all_assigned to true
Player FindPlayerByIndex();  // team - funct
Player FindPlayerByName();   // team - funct

// Create and allocate a
CreateTeam(int Nof_players);  // create a team with a given number of players
CreatePlayer(Character the_character)
AsignPlayer(Team theTeam, Player the_player);  // maybe take out team by making it a team-class-func
CreateDefaultTeam();  // create a 5 player team


CreatePlayerScore(Character the_character);



/* This is a structure that will be referenced by */
typedef struct Character_structure{

	string Character_name;
	int Character_id;

// value modifiers: soak_value, kill_value, To be done later
// personal attributes (from 1-100), example : waveclear 57/100, self-sustain 10/100. Talents affect and modify this values (also team-mates?)


/* This is a structure that will be referenced by */
} *Character;

//Character List; each have a name and an ID, also a talent list and 
// Item list, also has a name and an ID


typedef class Player_class{
	PlayerScore Score;
	Character character;
	bool item;
	Item the_item;

}* player;
struct PlayerScore{};

public class Host_Match 
{

private:
	Match_name;
	Match_leght;
	Match_current_time;
	Nof_players;
	Players;
	HostUI;
    Score (class);

	// functions


	void UpdateCurrentTime();

};

