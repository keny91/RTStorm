
#ifndef _CHARACTER_STRUCTS_H_
#define _CHARACTER_STRUCTS_H_ 



extern class Point;



/*	Anything that exists and can be clicked in the game, is an
entity. They might not have health bars, they might not move, they
remain entities.

This also serves as a base class for characters and structures.*/
typedef public class EntityClass
{
	EntityClass();
	~EntityClass();
} *Entity;



/*	Hitbox are for checking impacts of habilities or if a certain point is contained in it.
	There are multiple types of hitboxes, which will trigger a different "switch case" on call.
	The way we compare different hits on the same method is by setting a reference point (maybe also rotation)
	so we can define a hitbox around it.
	*/
typedef class HitboxClass
{
	enum HitboxType {Circular,Cone,Square,Rectangle};
	HitboxType theType;
	void* hitBoxref;

	Point* theRefPoint;

	bool isHitbyHitbox(Hitbox box);
		bool containsPoint();

}* Hitbox;


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
	Hitbox* AttArea;

	bool hasEffect;		// flag
	Effect AttEffect;

}*BasicAttack;
// do later (inherited from class damage source)






typedef class MovementClass 
{
	~MovementClass();
	MovementClass();

	// current MoveSpeed
	int currentMoveSpeed;
	// Base MoveSpeed of the character
	int baseMoveSpeed;



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