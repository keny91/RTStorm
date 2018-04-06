
#ifndef _BAR_H_
#define _BAR_H_ 

#include "Armor.h"

// I can keep this here without #include
extern class * Character; 

#define BAR_ALL_GOOD 0
#define BAR_REACHED_EMPTY 1
#define BAR_REACHED_MAX 2
// Certain effect checks
#define BAR_IS_ABOVE_TH 3  // above a %
#define BAR_IS_BELOW_TH 4

typedef class BarClass
{
protected:
	int currentBarValue;
	int maxBarValue;
	bool inmune;
	bool checkEmpty();
	int modifyValue(int value);
	int modifyValue(int value, int *excess);
	/*int checkModification(int value);*/
	int getPercentageFilled(int * perc_val_ref);
	int getPercentageMissing(int * perc_val_ref);
	int getAmountByPercentage(int  perc_val, int *ret_val);
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
	Character characaterParentRef;

	int setParent(void* character_reference);
	int getParent(void* character_reference);

public:
	// Function makes damage interact with target's Armor
	int takeDamage(int value, DamageType dmg_type);
	int takeDamage(int value, DamageType dmg_type ,int nof_ticks);
	int getHealthAmountByPercentage(int  perc_val, int *ret_val);
	int getHealthPercentageMissing(int * perc_val_ref);
	int getPercentageFilled(int * perc_val_ref);
	// Function makes healing interact with target's healModifier
	int healDamage(int value); 
	int healDamage(int value, int nof_ticks);
	
	HealthBarClass(int base_armor, Character char_reference);
	HealthBarClass();

}  *HealthBar;


typedef class ManaBarClass : public BarClass
{
protected:
	int setParent(void* character_reference);
	int getParent(void* character_reference);
	Character characaterParentRef;


public:
	// Function makes damage interact with target's Armor
	int modifyMana(int value);
	

	ManaBarClass(Character char_reference);
	ManaBarClass();
	~ManaBarClass();

}  *ManaBar;



#endif // _BAR_H_