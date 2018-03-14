#pragma once
#ifndef _BAR_H_
#define _BAR_H_ 

#include "Armor.h"

#define BAR_ALL_GOOD 0
#define BAR_REACHED_EMPTY 1
#define BAR_REACHED_MAX 2
// Certain effect checks
#define BAR_IS_ABOVE_TH 3  // above a %
#define BAR_IS_BELOW_TH 4

typedef class BarClass
{
protected:
	int current_value;
	int max_value;
	bool inmune;
	bool checkEmpty();
	int modifyValue(int value);
	int checkModification();
	int getPercentageFilled(double * perc_val_ref);
	bool isAboveTH(int perc_th);
	bool isBelowTH(int perc_th);
	virtual int setParent() = 0;  // must be implemented for child classes

public:
	BarClass();
	~BarClass();
	void SetCallBack_On_Empty(void*);

}  * Bar;



typedef class HealthBarClass : public BarClass 
{
protected:
	Armor armor;
	HealingModifier healingModifier;
	int setParent(Character character_reference);


public:
	// Function makes damage interact with target's Armor
	int takeDamage(int value); 
	int takeDamage(int value, int nof_ticks);
	// Function makes healing interact with target's healModifier
	int healDamage(int value); 
	int healDamage(int value, int nof_ticks);
	int CreateArmor(Armor* armorEmptyRef, int base_value = 0);
	
	HealthBarClass(int base_armor, Character char_reference);
	HealthBarClass();

}  *HealthBar;


typedef class ManaBarClass : public BarClass
{
protected:
	int setParent(Character character_reference);


public:
	// Function makes damage interact with target's Armor
	int modifyMana(int value);

	ManaBarClass(int base_armor, Character char_reference);
	ManaBarClass();
	ManaBarClass();

}  *ManaBar;



#endif // _BAR_H_