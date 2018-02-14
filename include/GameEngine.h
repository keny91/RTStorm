/*------------------ GameEngine.h  ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'GameEngine.h'			DESCRIPTION:
	
External reference meant for comunication between engines/projects

-----------------------------------------------------------------------------*/



/*	the following text will be cut to a different document:


here all declaration will be external functions and classes so we keep
both projects isolated. This will make these functions and structs addresable
while keeping their internal code hidden.
	
REMEMBER, these functions are what RT and Value engines will see from GameEngine

NO OTHER INCLUDES.

*/

#define 


typedef struct _GeStruct*            Ge;  // game instance
typedef struct _GePassageStruct*     GePassage;  // passage, englobes a series of connected events
typedef struct _GeRecognitionStruct* GeRecognition;  /* Single event to be parsed by the engine..
                                                      this one should be called when RT creates an 
													  event from a register*/


//_GeStruct is declared/defined in a different header (which includes GameEngine.h)

typedef void(*GeNewEventCallbackFunc)(GePassage passage, void* context);  // Maybe (void*) instead of RTpassage


/*------------------------------------------------------------------------------
 * GeFinalize
 *
 * Description:
 *  Finalizes the ...
 *----------------------------------------------------------------------------*/
extern void GeFinalizeGame();

extern int GeCreateGame(Ge* ge);

extern int GeDestroyGame(Ge ge);

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

*/





