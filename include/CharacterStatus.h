
#ifndef _CHARACTER_STATUS_H_
#define _CHARACTER_STATUS_H_ 


#define STATUS_ACTIVE 1
#define STATUS_EXPIRED 2
#define STATUS_APPLYED_OVERLAPED 3  // ex: if we want to apply a stun to an already stunned target.
#define STATUS_APPLYED_NOT_OVERLAPED 4
#define INVALID_STATUS -1



/***** Status:

Description: status are pre-defined modification which will label
characters/buildings/entities based on their current situation.

This will later help calculate value in the value engine. Value will
increase the more significant the status applied, therefore we
will take into account a possible overlap output.

*/

enum StatusLabel 
{
Stunned, Slowed, Rooted, Dazed, Unstopable, Protected, PhysicalProtected, MagicProtected, Blinded, Stopped
};


typedef enum DebufLabels 
{ Polymorphed, Invulnerable, Sleep, Trapped ,Stunned, Slowed, Rooted, Dazed, Unstopable, Protected, PhysicalProtected, MagicProtected, Blinded, Stopped 
} DebufStatusLabel ;

typedef struct StatusStruct
{

	bool active;
	double duration;
	ActiveTimeSpan timeWindow;
	StatusLabel statusName;
public:
	int ActivateStatus(double duration , double time_overlap);
	int ActivateStatus(double start_time, double end_time, double time_overlap);
	bool isActive(double Time);

}*Status;


/* Invulnerable = Unstoppable + Protected*/

typedef struct CharacterStatusStruct 
{
	Status StunnedStatus;
	Status SlowedStatus;
	Status RootedStatus;
	Status DazedStatus;
	Status UnstopableStatus;
	Status ProtectedStatus;
	Status PhysicalProtectedStatus;
	Status MagicProtectedStatus;
	Status BlindedStatus;
	Status StoppedStatus;
	// status unkillable

	bool isActiveStatus(double* currentTime, StatusLabel status);  
	int applyTemporal(AlterationStatus theStatusChange, double duration);
	bool applyStatus(StatusLabel theStatus, double duration);


private:
	int CharacterStatusStruct::getStatus(StatusLabel status, Status* theStatusRef);

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


#endif  // _CHARACTER_STATUS_H_ 
