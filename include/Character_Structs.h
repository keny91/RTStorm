
#ifndef _CHARACTER_STRUCTS_H_
#define _CHARACTER_STRUCTS_H_ 



extern class Area;



/*	Anything that exists and can be clicked in the game, is an
entity. They might not have health bars, they might not move, they
remain entities.

This also serves as a base class for characters and structures.*/
typedef public class EntityClass
{
	EntityClass();
	~EntityClass();
} *Entity;




/*	Basic Attacks is a class to represent the modifiable basic damage
that many characters do via right click*/
typedef class BasicAttackClass
{
	int BasicAttValue;   // current
	int Base_BasicAttValue;  // base value loaded from xml

	double Base_AttSpeedValue; // base value loaded from xml
	double AttSpeedValue;	// current

	double Base_AttSpeedRange; // base value loaded from xml
	double AttSpeedRange; // current

	bool hasAreaDamage;  // flag
	Area AttArea;

	bool hasEffect;		// flag
	Effect AttEffect;



}*BasicAttack;
// do later (inherited from class damage source)




typedef class MovementClass 
{
	~MovementClass();
	MovementClass();

	// current MoveSpeed
	int MoveSpeed;
	// Base MoveSpeed of the character
	int Base_MoveSpeed;



	MapPosition Position;

} *Move;



/*  */
typedef public class SizeClass
{
	~SizeClass();
	SizeClass();

} *Size;








extern class CharacterValueModTable;
extern class CharacterStats;
//extern class EntityClass;   // parent class



enum EnergySource { Mana, Energy, Manaless, Rage, Other };









#endif // _CHARACTER_STRUCTS_H_