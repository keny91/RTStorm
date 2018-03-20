#pragma once

#ifndef _GAMESTRUCTS_H_
#define _GAMESTRUCTS_H_

#include "GE_MSGs.h"


typedef int ModifierType;
typedef int EffectType;

extern struct end_effect_event;


typedef class EffectClass
{
public:
	EffectType type;
	int duration;
	int tick_frequency;



protected:
	void* time_event;  // time event might have multiple triggers


} *Effect;


// abstract class; use it as the parent model for the rest
typedef class modifierClass
{

public:
	//
	//void* reference;   // class/struct that has this mod associated
	//ModifierType type;  // 


protected:   // children will have these defined

	int maxCap, minCap;
	int modValue;
	int baseValue;
	bool inverseProportional;

	int applyModifier(int value);
	int modifyValue(int amount);
	virtual bool reachedCap();
	virtual int getParent(void* ref) = 0;  // pure virtual -> must be redifined 
									// depending on the child we know which is our type of parent (type of pointer returning)
	virtual int setParent(void* ref) = 0;
									//private:	// no-sense to declare any privates in the parent
}  * modifier;





#endif // _GAMESTRUCTS_H_