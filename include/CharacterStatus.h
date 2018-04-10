#pragma once


#define STATUS_ACTIVE 1
#define STATUS_EXPIRED 2
#define INVALID_STATUS -1


enum StatusLabel 
{
Stunned, Slowed, Rooted, Dazed, Unstopable, Protected, PhysicalProtected, MagicProtected, Blinded, Stopped
};


typedef enum DebufLabels 
{ Polymorphed ,Stunned, Slowed, Rooted, Dazed, Unstopable, Protected, PhysicalProtected, MagicProtected, Blinded, Stopped 
} DebufStatusLabel ;

typedef struct StatusStruct
{

	bool active;
	double duration;
	ActiveTimeSpan timeWindow;
	StatusLabel statusName;
public:
	double ActivateStatus(double duration);
	double ActivateStatus(double start_time, double end_time);
	bool isActive(double Time);

}*Status;


/* Invulnerable = Unstoppable + Protected*/

typedef struct CharacterStatusStruct 
{
	Status Stunned;
	Status Slowed;
	Status Rooted;
	Status Dazed;
	Status Unstopable;
	Status Protected;
	Status PhysicalProtected;
	Status MagicProtected;
	Status Blinded;
	Status Stopped;
	// status unkillable

	bool isActiveStatus(double currentTime, StatusLabel status);  
	int applyTemporal(AlterationStatus theStatusChange, );
	bool applyStatus();


} * CharacterStatus;



typedef struct AlterationStatusStruct
{
	DebufStatusLabel name;


}* AlterationStatus, * Buff;

typedef struct ActiveTimeSpanStruct
{
	double StartTime;
	double EndTime;

	bool isInsideInterval();

}*ActiveTimeSpan;

