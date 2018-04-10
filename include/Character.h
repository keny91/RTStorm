
#ifndef _CHARACTER_H_
#define _CHARACTER_H_ 

#include "Bar.h"
#include "du.h"
//extern enum ArmorType;


extern class BasicAttack;  // do later (inherited from class damage source)

typedef class CharacterClass 
{
protected:
	int SetMaxHP(int value);
	int SetMaxMana(int value);
	int ModifyHP(int value);
	int ModifyMana(int value);
	int ModifyArmor(ArmorType type, int value);
	int SetBaseArmor(ArmorType type ,int value);
	int SetBasicAttackDamage(int value);
	int MountUp();
	int ApplyDamage(int value, DamageType type);
	int ApplyHeal(int value);
	int GetStatus();

	DuList StatusQueue;  // any entiti will have a queue
							// this queue might have the detailed time events (and a reference to the MAIN time queue)

	Hero heroParentRef;

		//int BasicAttack;

	bool Mountable;
	int MoveSpeed;
	HealthBar healthBar;
	ManaBar manaBar;

	bool isDead;


	BasicAttack basicAttack;


public:
	int setParentHero(void * ref);
	int getParentHero(void * ref);

} Character;


#endif  // _CHARACTER_H_ 
