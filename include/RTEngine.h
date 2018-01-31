

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
 


// An engine based on different sequential modules

typedef int (*IntradaLiveModuleCreateSettingsFunc)(void** modulesettings);

typedef int (*IntradaLiveModuleSettingFunc)(void* modulesettings, const char* settingAction, void* value, int valueAsString);

typedef int (*IntradaLiveModuleDestroySettingsFunc)(void** modulesettings);



/** Represents a IntradaLiveModule instance. Each module has to be registered with an instance of this struct */
typedef struct _IntradaLiveModuleStruct
{
  const char*                             moduleName;
  const char*                             version;
  IntradaLiveModuleInitFunc               initFunc;
  IntradaLiveModuleFinitFunc              finalizeFunc;
  IntradaLiveModuleAddDataFunc            addDataFunc;
  IntradaLiveModuleCreateFrameSourceFunc  createFrameSourceFunc;
  IntradaLiveModuleDestroyFrameSourceFunc destroyFrameSourceFunc;
  IntradaLiveModuleCreateDataFunc         createDataFunc;
  IntradaLiveModuleCloneDataFunc          cloneDataFunc;
  IntradaLiveModuleDestroyDataFunc        destroyDataFunc;
  IntradaLiveModuleGetDataFunc            getDataFunc;
  IntradaLiveModuleSettingFunc            settingFunc;
  IntradaLiveModuleCreateSettingsFunc     createSettingsFunc;
  IntradaLiveModuleDestroySettingsFunc    destroySettingsFunc;   
  int                                     index;        /**< private field, do not use */
  struct _IntradaLiveModuleStruct*        nextModule;   /**< private field, do not use */
} IntradaLiveModule;

typedef enum 
{
  DATA_PUSH_TO_NEXT_MODULE = 0,
  DATA_DESTROY,
  DATA_HOLD
} DataAction;


// if sequential this is how you add a module to the chain process
// Each module should have a functionality -> from and input (if right input) to an output (that ->nextModule uses as an input)  
// The engine will have multiple modules -> at the end -> callBacks (setOutputCB & setErrorCB) 

/**
 * @see IntradaLiveCore.h
 */
int IntradaLiveCoreAddModule(IntradaLiveModule *module)
{
  if (gl_theProcess.nofModules==MAX_NOF_MODULES)
    return INTRADALIVE_CORE_RETURN_MAX_NOF_MODULES_REACHED;

  gl_theProcess.modules[gl_theProcess.nofModules] = module;
  gl_theProcess.modules[gl_theProcess.nofModules]->index = gl_theProcess.nofModules;
  gl_theProcess.modules[gl_theProcess.nofModules]->nextModule = NULL;
  if (gl_theProcess.nofModules>0)
  {
    gl_theProcess.modules[gl_theProcess.nofModules-1]->nextModule = gl_theProcess.modules[gl_theProcess.nofModules];
  }

  gl_theProcess.nofModules++;
  return INTRADA_RETURN_OK;
}

