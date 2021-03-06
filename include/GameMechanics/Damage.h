#pragma once

#ifndef _DAMAGE_H_
#define _DAMAGE_H_


#include "GameStructs.h"

//typedef int damageType;

enum DamageType {
	TrueDamage, PhysicalDamage, MagicDamage, PercentDamege
};
// condition could still be Destroy core, but core only can TakeDamage() through objectives.

enum AttackType { areaDamage, singleTarget, skillshot, nova, autoAttack, };

class Attack {
public:
	Attack();
	~Attack();
protected:
	int damageValue;
	AttackType type;


	virtual int OnImpact();
	virtual int CreateDamage();
	virtual int CreateEffect();
};


class Damage {

protected:
	int value;
	DamageType type;
	
	bool isModifiable;
	bool ignoresArmor;

	void* damageSource;
	void* damageTarget;


	int applyDamage(int value);
	int loadAttack();

};

// move this one to Damage
class AttackModifier : protected modifierClass
{

};

#endif // _DAMAGE_H_