
#ifndef _CHARACTER_H_
#define _CHARACTER_H_ 

#include "Bar.h"
//extern enum ArmorType;

typedef class CharacterClass 
{
protected:
	int SetMaxHP(int value);
	int SetMaxMana(int value);
	int ModifyHP(int value);
	int ModifyMana(int value);
	int SetBaseArmor(ArmorType type ,int value);
	int SetBasicAttackDamage(int value);
	int MountUp();
	int ApplyDamage(int value, DamageType type);
	int ApplyHeal(int value);
	int GetStatus();


		//int BasicAttack;

		bool Mountable;
	int MoveSpeed;
	HealthBar healthBar;
	ManaBar manaBar;
	bool isDead;

	BasicAttack basicAttack;


public:

} Character;


#endif  // _CHARACTER_H_ 
