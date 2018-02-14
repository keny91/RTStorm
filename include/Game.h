/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Game.h'			DESCRIPTION:
	
Storage of game event functions.

Ex: Death, score, ...

-----------------------------------------------------------------------------*/

#include "du.h"
#include "Score.h"
#include <string.h>
#include <iostream>
using namespace std;

extern class Team;

// all this is defined in score.h so it is not necessary
extern class ScoreCoreGame;
extern class ScorePointedGame;
extern class TeamScore;
extern class Map;
extern class RTEvent;

// all these should be defined in RT.h
extern struct RTData;
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





typedef class Game
{
	
public: 
	Game();
	// just an internal call to Game(), and player and map linkage.
	static void CreateGame(Map the_Map, Team teamA, Team teamB, Game* game_empty_ptr_ref); 
	~Game();

protected:
	int duration;   // In seconds / time?
	TeamScore* score_team_red;	// reference to score structure
	TeamScore* score_team_blue;
	
	Team* team_red;	//	 to team structure
	Team* team_blue;
	
	Map* the_map;
	
	RTEvent * event_list; // tribute/tower/objective spawn

	// this will act better as internal structures	
	class Team {};
	class Player {};
	extern class TeamScore;

	// Functions
	
	int StartGame();
	// next probably goes in "ENGINE"
	int SetRTContextCallback( (void *) funct);
	int SetRTNextEventCallback(int timing, (void *) funct );  // New thread should trigger an event when the marked time comes.
	int InitializeKeyPressCallbacks();  // predefined function that compiles a bunch of ON-KEY-PRESS callbacks.  
	int InitHostEngine();
	int CreateTeam(Team* the_team);
	int CreatePlayer(Player* the_player);

	
	
	// Get/Set functions
	
	
private:
	

} GC;



// shoul this be here?
class Effect {
public:
	// Effect(); this is the root/parent class

	effecttype type;	
	//Effect();
	int hasValidValue();
		;
protected:
	
	;
private:
	;
};





/*	the following text will be cut to a different document:
GameEngine.h

here all declaration will be external functions and classes so we keep
both projects isolated. This will make these functions and structs addresable
while keeping their internal code hidden.
	
REMEMBER, these functions are what RT and Value engines will see from GameEngine

NO OTHER INCLUDES.

*/

typedef struct _GeStruct*            Ge;  // game instance
typedef struct _GePassageStruct*     GePassage;  // passage, englobes a series of connected events
typedef struct _GeRecognitionStruct* GeRecognition;  // Single event to be parsed by the engine..
                                                     // this one should be called when RT creates an 
						     // event from a register


//_GeStruct is declared/defined in a different header (which includes GameEngine.h)


/*------------------------------------------------------------------------------
 * GeFinalize
 *
 * Description:
 *  Finalizes the ...
 *----------------------------------------------------------------------------*/
extern void GeFinalizeGame(void);

extern int GeCreateGame(Ge* ge);

// then in the .c file
MT_PUBLIC int MtCreateMt(Mt* mt)
{
    int result;
    Mt the_mt;


    if (mt == NULL) return MT_RETURN_NULL_POINTER;

    if (DuInitialize(NULL)!=DU_RETURN_OK)
      return MT_RETURN_ILLEGAL_VERSION;

    the_mt = (Mt)calloc(1, sizeof(MtStruct));
    if (the_mt == NULL) return MT_RETURN_OUT_OF_MEMORY;
	
#ifdef MT_DEBUG
	MtDebugLog = fopen(MT_DEBUG_LOG_NAME,"w");
	fprintf(MtDebugLog, "Creating context... \n" );
#endif

    result = MtCreateData(&the_mt->data);
    if (result != MT_RETURN_OK)
    {
#ifdef MT_DEBUG
	fprintf(MtDebugLog, "\tError Creating mt->data: Error %d \n ",  result);
#endif
        free(the_mt);
        return result;
    }
    the_mt->data->mt = the_mt;

    result = MtCreateConfig(&the_mt->config);
    if (result != MT_RETURN_OK)
    {
#ifdef MT_DEBUG
	fprintf(MtDebugLog, "\tError Creating mt->config : Error %d \n ",  result);
#endif
        MtDestroyData(the_mt->data);
        free(the_mt);
        return result;
    }

    MtProcessEnvironment(the_mt);

    /* Some starting values may be set through the configuration. */
    the_mt->data->last_delivered_direction = the_mt->config->initial_direction;
    the_mt->data->speed = the_mt->config->initial_speed;

    *mt = the_mt;

#ifdef MT_DEBUG
	fprintf(MtDebugLog, "\t Done... MT context created. \n " );
#endif

    return MT_RETURN_OK;   
}



extern int MtDestroyMt(Ge ge);

// and then in a .C file
MT_PUBLIC int MtDestroyMt(Mt mt)
{
    int result;

    if (mt == NULL) return MT_RETURN_NULL_POINTER;

    MtFlushFilter(mt);

    result = MtDestroyData(mt->data);
    if (result != MT_RETURN_OK) return result;

    result = MtDestroyConfig(mt->config);
    if (result != MT_RETURN_OK) return result;

    free(mt);

    return MT_RETURN_OK;
}


typedef void (*GeNewEventCallbackFunc)(GePassage passage, void* context);  // Maybe (void*) instead of RTpassage

extern int GeSetNewEventCallback(
        Ge ge, GeNewEventCallbackFunc callback, void* context)

	/*
MT_PUBLIC int MtSetNewPassageCallback(Mt mt, MtNewPassageCallbackFunc callback, void* context)
{
    if (mt == NULL) return MT_RETURN_NULL_POINTER;

    mt->data->new_passage_callback_func = callback;
    mt->data->new_passage_callback_context = context;

    return MT_RETURN_OK;
}

// defined in mt->data->... as



// then summon the stored function as
(*mt->data->new_passage_callback_func)(passage, mt->data->new_passage_callback_context);
	MtNewPassageCallbackFunc new_passage_callback_func;
	void*                    new_passage_callback_context;
	*/




/* clean this 

// in shared mt.h file
extern int MtSetNewPassageCallback(
        Mt mt, MtNewPassageCallbackFunc callback, void* context);
// callback function definition in mt.h
typedef void (*MtNewPassageCallbackFunc)(MtPassage passage, void* context);


// in definition
MT_PUBLIC int MtSetNewPassageCallback(Mt mt, MtNewPassageCallbackFunc callback, void* context)
{
    if (mt == NULL) return MT_RETURN_NULL_POINTER;

    mt->data->new_passage_callback_func = callback;
    mt->data->new_passage_callback_context = context;

    return MT_RETURN_OK;
}


// external call
MtSetNewPassageCallback(mt,MtNewPassageCallback,NULL);

// MtNewPassageCallback definition 
// NOTE is respects the definition in mt.h
static void MtNewPassageCallback(MtPassage passage, void* context)
{
  IntradaLiveDataStruct* pData;
  IntradaLiveDataStruct* pClonedData;
  const IntradaLiveSettingsStruct* pSettings;

  CombineModData* pModData;
  CombineModSettings* pModSettings;

...




// need a template for callback functions
/*------------------------------------------------------------------------------
 * MtNewPassageCallbackFunc
 *
 * Description:
 *  Signature for a callback function that can be registered with this module.
 *  The function will be called for each newly tracked passage.
 *----------------------------------------------------------------------------*/
typedef void (*RTContextCallbackFunc)(RTpassage passage, void* context);  // Maybe (void*) instead of RTpassage
typedef void (*SetRTNextEventCallbackFunc)(RTpassage passage, void* context);



*/





