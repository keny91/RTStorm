
#include "Game.h"


// then in the .c file
int GeCreateGame(Ge* ge)
{
	int result;
	Ge the_game;


	if (mt == NULL) return MT_RETURN_NULL_POINTER;

	if (DuInitialize(NULL) != DU_RETURN_OK)
		return MT_RETURN_ILLEGAL_VERSION;

	the_mt = (Mt)calloc(1, sizeof(MtStruct));
	if (the_mt == NULL) return MT_RETURN_OUT_OF_MEMORY;

#ifdef MT_DEBUG
	MtDebugLog = fopen(MT_DEBUG_LOG_NAME, "w");
	fprintf(MtDebugLog, "Creating context... \n");
#endif

	result = MtCreateData(&the_mt->data);
	if (result != MT_RETURN_OK)
	{
#ifdef MT_DEBUG
		fprintf(MtDebugLog, "\tError Creating mt->data: Error %d \n ", result);
#endif
		free(the_mt);
		return result;
	}
	the_mt->data->mt = the_mt;

	result = MtCreateConfig(&the_mt->config);
	if (result != MT_RETURN_OK)
	{
#ifdef MT_DEBUG
		fprintf(MtDebugLog, "\tError Creating mt->config : Error %d \n ", result);
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
	fprintf(MtDebugLog, "\t Done... MT context created. \n ");
#endif

	return MT_RETURN_OK;
}
