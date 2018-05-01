
#ifndef _CHARACTER_H_
#define _CHARACTER_H_ 




#include "Bar.h"
#include "du.h"
#include "Character_Structs.h"
//extern enum ArmorType;









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

	CharacterClass();
	~CharacterClass();

protected:
	int SetMaxHP(int value);
	//int SetMaxMana(int value);
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



	// Maybe create a class for movement?
	Move Movement;
	HealthBar healthBar;
	//ManaBar manaBar;

	// void * so any reference can be assigned to this EnergyBar ref?
	EnergySource energySource;


	
	//Hero heroParentRef;

	// flag that marks is a character is 
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



typedef class HeroCharacterClass : CharacterClass
{
	HeroCharacterClass();
	~HeroCharacterClass();

	int SetMaxMana(int value); // max energy?

	// extra definitions:
	// should this be only defined for Hero-characters?
	bool isRespawnable;

	// is multiple Heroes -> lost vikings/rexxar
	bool isMultipleHeroes;

	// set the references of all the heroes linked to the player in the different heroes
	// ex: setCallbackLinkMultipleHeroes(setRexxar(), [Rexxar_ref,Misha_ref]);
	int setCallbackLinkMultipleHeroes(void* funct, Hero the_heroes_list);


	// is multiple Players -> chogall
	// cho & gall are two heroes
	bool isMultiplePlayers;
	//	unnecessary ?
	int setCallbackLinkMultiplePlayers(void* funct, Player the_heroes_list);

	// reference to the hero which is the class  this one.
	Hero parentHeroRef;
	EnergySource energySource;

}*HeroCharacter;


#endif  // _CHARACTER_H_ 
