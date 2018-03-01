#pragma once

#ifndef _ARMOR_H_
#define _ARMOR_H_

#include "Game.h"
#include "bar.h"
#include "GameStructs.h"

typedef class _ArmorClass
{
private:
	int current_value;
	MagicArmor magicArmor;
	PhysicalArmor physicalArmor;


	int base_value;
	int max_value;
	bool inmune;


public:
	_ArmorClass();
	_ArmorClass(int base_value);
	~_ArmorClass();
	int takeDamage(int damage_per_tick, int nof_ticks);
	int takeDamage(int damage_per_tick); // polymorphism
//	int healDamage();

} ArmorClass, *Armor;


typedef class _MagicArmorClass : modifierClass 
{

} MagicArmorClass, * MagicArmor;


typedef class _PhysicalArmorClass : modifierClass
{

} PhysicalArmorClass, *PhysicalArmor;


typedef class _HealingModifierClass : modifierClass
{
	int value;
} 
HealingModifierClass, * HealingModifier;

#endif // _ARMOR_H_
