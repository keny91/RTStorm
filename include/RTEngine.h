

/*------------------------------------------------------------------------------
 * MT_RETURN_xxx
 *
 * Description:
 *  Return values for the various functions within the RT engine.
 *----------------------------------------------------------------------------*/
#define RT_RETURN_OK                  0
#define RT_RETURN_FILE_NOT_FOUND      1
#define RT_RETURN_INVALID_INPUT       2
#define RT_RETURN_UNKNOWN_ERROR       3
#define RT_RETURN_NULL_POINTER        4
#define RT_RETURN_ILLEGAL_VIEWPORT    5
#define RT_RETURN_VIEWPORT_NOT_SET    6
#define RT_RETURN_DU_ERROR            7
#define RT_RETURN_ILLEGAL_VERSION     8



typedef struct _RtStruct
{
    RTData   data;
    TRConfig config;
} RTStruct; /* RT points to this. */

typedef struct _RTStruct*   Rt;



// Create/destroy... Rt classes <- the idea is that there is only one... but HOST and Value have a reference to it.
// in intradalive is a dll so everything is controlled from the other engine (creation, setCBs ,feeding data)
// Also intradaLiveCore is also a lib. iNTRADALIVECORE also stores 

/*------------------------------------------------------------------------------
 * RTNewPassageCallbackFunc
 *
 * Description:
 *  Signature for a callback function that can be registered with this module.
 *  The function will be called for each newly tracked passage.
 *----------------------------------------------------------------------------*/
typedef void (*RtCCallbackFunc)(MtPassage passage, void* context);
typedef void (*RtWillRemovePassageCallbackFunc)(MtPassage passage, void* context);

extern int MtSetNewPassageCallback(
        Mt mt, MtNewPassageCallbackFunc callback, void* context);


extern int MtSetWillRemovePassageCallback(
        Mt mt, MtNewPassageCallbackFunc callback, void* context);


// AND IN THE CODE 
 MtSetReleaseEventContextCallback(mt,MtReleaseEventContextCallback,NULL); 
  MtSetNewPassageCallback(mt,MtNewPassageCallback,NULL);
 //THEN... THE COMUNICATION IS STABLISHED AFTER CREATING AN MT OBJECT -> THEN WE USE External functions to communicate with it
 rc = MtAddRecognitionEvent(mt,dataToSendToMt->timestamps[0],recognition,(MtEventContext)dataToSendToMt,
                                         &canReleaseContext);
 
