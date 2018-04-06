#pragma once

#ifndef _ARMOR_H_
#define _ARMOR_H_

#include "Game.h"
#include "bar.h"
#include "GameStructs.h"



// SET PARAMS
#define MAX_ARMOR_CAP 75
#define MIN_ARMOR_CAP -30
#define HUNDRED_PERC_VAL 100

enum ArmorType {
	FullArmor, Magical, Physical
};


// Move to damage?
//extern enum DamageType;  // repeat definition
enum DamageType {
	TrueDamage, PhysicalDamage, MagicDamage, PercentDamege
};


typedef class ArmorClass
{
private:
	int currentArmorValue;
	MagicArmor magicArmor;
	PhysicalArmor physicalArmor;
	HealthBar parentHealthRef;

	int baseArmorValue;
	int minArmorCap, maxArmorCap;
	bool inmune;
	int addPermanentArmor(ArmorType type, int value);
	int baseValue;


public:
	//int CreateArmor(Armor* armorEmptyRef, int base_value = 0);
	~ArmorClass();
	ArmorClass();
	ArmorClass(int base_value);
	int takeDamage(int damage_per_tick, int nof_ticks);
	int takeDamage(int damage, DamageType dmg_type); // polymorphism
	int getHealthBarRef(void * ref);
	int setHealthBarRef(void * ref);
	int modifyArmor(ArmorType type, int value);
	bool checkValidArmor();
//	int healDamage();

} *Armor;



typedef class  ArmorModifierClass : public  modifierClass 
{

protected:
	//typedef ArmorValue modValue;
	ArmorType armorType;
	Armor armorParentRef;
	//HealthBar healthParentRef;
	bool inmune;

	// redefined for future childs
	int modValue;
	int maxCap;
	int minCap;
	int baseValue;
	bool inverseProportional;
	
	/* Take damage -> create a ref to health*/
public:
	int calculateDamage(int damage_per_tick, int nof_ticks, DamageType dmg_type);
	int calculateDamage(int damage); // polymorphism
	int modifyValue(int amount);
	int setPermanentArmor(int value);
	int getParent(void* ref) override;
	int setParent(void* ref) override;
}*ArmorModifier;




typedef class MagicArmorClass : public ArmorModifierClass
{
	/*int applyModifier(int value);
	int modifyValue(int amount);
	bool reachedCap();
	void getParent() = 0;*/

protected:
	//int setParent(void* ref);
	//int getParent(void* ref);
	//void getParent();
	public:
	MagicArmorClass();
	~MagicArmorClass();

} * MagicArmor;


typedef class PhysicalArmorClass : public ArmorModifierClass
{


public:
	PhysicalArmorClass();
	~PhysicalArmorClass();
	
}  *PhysicalArmor;


typedef class HealingModifierClass : modifierClass
{

protected:
	HealthBar healthBarRef;
	int calculateHeal(int healing);

public:
	//void getParent(HealthBar* emptyRef);  // re-writting virtual
	int getParent(void* ref) override;
	int setParent(void* ref) override;
} 
 * HealingModifier;

#endif // _ARMOR_H_
