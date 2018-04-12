
#ifndef _CHARACTER_H_
#define _CHARACTER_H_ 




#include "Bar.h"
#include "du.h"
//extern enum ArmorType;


extern class BasicAttack;  // do later (inherited from class damage source)
extern class CharacterValueModTable;
extern class CharacterStats;
extern class EntityClass;   // parent class



enum EnergySource {Mana, Energy, Manaless, Rage, Other};


/*** Description: Character

		Description: any entity can be a character.
		Characters have a healthbar, move and have a basic attack.
		(Some may be linked to a hero which they report their value to)

		Characters are created from a character template.

		Character examples: zagara´s roaches/hydras, zul´s skellys


		Characters are loaded from an xml. CharacterParser class:
		Insert ".xml"
		
		CreateCharacter(label character);
		CreateHeroCharacter(label heroCharacter){
		xmlpath="./data/characters/"+characterLabel/dictionary.toString()+".xml";
		
		// load whatever data is in the xml labels into classes
		loadCharacter(Character the_char, xmlpath);

		}


*/
typedef class CharacterClass : public EntityClass
{
protected:
	int SetMaxHP(int value);
	int SetMaxMana(int value);
	int ModifyHP(int value);
	int ModifyMana(int value);
	int ModifyArmor(ArmorType type, int value);
	int SetBaseArmor(ArmorType type, int value);
	int SetBasicAttackDamage(int value);
	int MountUp();
	int ApplyDamage(int value, DamageType type);
	int ApplyHeal(int value);
	int GetStatus();

	int getCurrentHP();
	double getCurrentHPpercentage();


	DuList StatusQueue;  // any entiti will have a queue
							// this queue might have the detailed time events (and a reference to the MAIN time queue)

	

	//int BasicAttack;

	bool Mountable;
	bool isHeroicTarget; //
	bool hasMana;

	int MoveSpeed;
	HealthBar healthBar;
	//ManaBar manaBar;
	EnergySource energySource;

	Hero heroParentRef;

	bool isDead;

	//
	BasicAttack *basicAttack; // common to all 

	// Specific Value Table unique for each character
	CharacterValueModTable *modifierTable;

	// 
	CharacterStats * stats;

public:
	int setParentHero(void * ref);
	int getParentHero(void * ref);

}*Character;



typedef class HeroCharacterClass : EntityClass
{
	HeroCharacterClass();
	HeroCharacterClass();
	~HeroCharacterClass();

}*HeroCharacter;


#endif  // _CHARACTER_H_ 
