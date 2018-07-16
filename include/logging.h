#ifndef _LOGGING_H_
#define _LOGGING_H_ 

#include <stdio.h>
#include <fstream>
#include <time.h>
using namespace std;

#define ErrorLogName "error_log.txt"
#define WarningLogName "warning_log.txt"
#define MessageLogName "message_log.txt"

#define LoggingPath

//using std;
FILE* ErrorLogFile;
FILE* WarningLogFile;
FILE* MessageLogFile;


enum logType
{
	ErrorLog, WarningLog, MessageLog
};



void InitLog(char* name, logType log_type)
{

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	char* alt;
	char buffer[200];
	char*path = ".//logs//";
	char timebuffer[80];

	strftime(timebuffer, 80, "_%Y-%m-%d.", now);

	switch (log_type)
	{
	case ErrorLog:
		
		strcat(buffer, path);
		strcat(buffer, name);
		strcat(buffer,timebuffer);
		strcat(buffer, ErrorLogName);

		//alt = ;
		ErrorLogFile = fopen(buffer, "w");
		break;

	case WarningLog:
		strcat(buffer, path);
		strcat(buffer, name);
		strcat(buffer, timebuffer);
		strcat(buffer, WarningLogName);

		//alt = ;
		WarningLogFile = fopen(buffer, "w");
		break;

	case MessageLog:
		strcat(buffer, path);
		strcat(buffer, name);
		strcat(buffer, timebuffer);
		strcat(buffer, MessageLogName);

		//alt = ;
		MessageLogFile = fopen(buffer, "w");
		break;

	default:
		break;
	}

};


void InitLogs()
{
	InitLog("debug", ErrorLog);
	InitLog("debug", WarningLog);
	InitLog("debug", MessageLog);

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
	fprintf(MessageLog,"%s \n" ,input);
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