#pragma once

#ifndef _ARMOR_H_
#define _ARMOR_H_

#include "GameStructures.h"
#include "bar.h"
#include "Game.h"

class Armor
{
private:
	int current_value;
	int base_value;
	int max_value;
	bool inmune;
	HealthBar * health_target;


public:
	Armor();
	Armor(int base_value);
	~Armor();
	int takeDamage(int damage_per_tick, int nof_ticks);
	int takeDamage(int damage_per_tick); // polymorphism
	int healDamage();

};


class MagicArmor : modifier

#endif // _ARMOR_H_
