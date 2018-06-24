#ifndef _LOGGING_H_
#define _LOGGING_H_ 

#include <stdio.h>
#include <fstream>
using namespace std;

#define ErrorLogName "error_log.txt"
#define WarningLogName "warning_log.txt"
#define MessageLogName "message_log.txt"

//using std;
FILE* ErrorLog;
FILE* WarningLog;
FILE* MessageLog;



void LogMessage(char * input) {
	FILE* aux = fopen(MessageLogName, "w+");
	if (aux == NULL) {
		// do nothing
	}
	else
	{
		// assing the reference created to
		MessageLog = aux;
	}
	fprintf(MessageLog,"%s \n" ,input);
#ifdef DEBUG_GE
	//print to console
	printf(MessageLog, "GE_ENGINE_MESSAGE: %s \n", input);
#endif
};

void LogMessage(char * input) {
	FILE* aux = fopen(MessageLogName, "w+");
	if (aux == NULL) {
		// do nothing
	}
	else
	{
		// assing the reference created to
		MessageLog = aux;
	}
	fprintf(MessageLog, "%s \n", input);
#ifdef DEBUG_GE
	//print to console
	printf(MessageLog, "GE_ENGINE_MESSAGE: %s \n", input);
#endif
};


void LogWarning(char * input) {
	FILE* aux = fopen(WarningLogName, "w+");
	if (aux == NULL) {
		// do nothing
	}
	else
	{
		// assing the reference created to
		WarningLog = aux;
	}
	fprintf(WarningLog, "%s \n", input);
#ifdef DEBUG_GE
	//print to console
	printf(MessageLog, "GE_ENGINE_WARNING: %s \n", input);
#endif
};


void LogError(char * input) {
	FILE* aux = fopen(WarningLogName, "w+");
	if (aux == NULL) {
		// do nothing
	}
	else
	{
		// assing the reference created to 
		ErrorLog = aux;
	}
	fprintf(ErrorLog, "%s \n", input);
#ifdef DEBUG_GE
	//print to console
	printf(MessageLog, "GE_ENGINE_ERROR: %s \n", input);
#endif
};




void CloseFile(FILE* log) {
	fclose(log);
};

void CloseLogFiles() {
	CloseFile(ErrorLog);
	CloseFile(MessageLog);
	CloseFile(WarningLog);
};


#endif