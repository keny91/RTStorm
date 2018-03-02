#pragma once
#ifndef _BAR_H_
#define _BAR_H_ 

#include "Armor.h"


typedef class BarClass
{
protected:
	int current_value;
	int max_value;
	bool inmune;
	bool checkEmpty();
	int modifyValue();
	


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
	

public:
	// Function makes damage interact with target's Armor
	int takeDamage(int value); 
	int takeDamage(int value, int nof_ticks);
	// Function makes healing interact with target's healModifier
	int healDamage(int value); 
	int healDamage(int value, int nof_ticks);
	int CreateArmor(Armor* armorEmptyRef, int base_value = 0);
	
	HealthBarClass(int base_armor);
	HealthBarClass();

} HealthBarClass, *HealthBar;

#endif // _BAR_H_