#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include <string>
#include "du.h"

using namespace std;


// should not include other game headers

// depending on which map, the game will init different params on creation
static enum MapPool {
	Cursed_Hollow, Blackhearts_Bay, Garden_of_Terror, Towers_of_Doom, Sky_Temple, Volskaya_Foundry, \
	Tomb_of_Spiderqueen, Haunted_Mines, Hanamura, Battlefield_of_Eternity, Punishers, Braxis_Holdout, Warhead_Junktion
};
// each of the above should have an individual

// win condition -> enemy points reach 0
static enum Map_Score_Based { Towers_of_Doom_p, Hanamura_p };
// condition could still be Destroy core, but core only can TakeDamage() through objectives.

static enum StructureType {
	Tower, Fort, Keep, Core, Wall, Fountain
};


static int ReadStructureFromLine(string line, Structure* structure);

typedef struct {
	int x;
	int y;
} XYpositionStruct, *MapPosition;

typedef class _MapClass
{
private:

protected:
	//string mapName;
	MapPool map;
	DuList originalStructures;
	DuList redTeamStructures;
	DuList blueTeamStructures;
	const string resourceFolder;

	virtual int InitMap();		// initializes a different score system and different structures
	(void *) mapScore;  // Each map has a different map score
	int LoadInitialStructures();   // load the structures based on a config file in the "resourceFolder" path.


public:
	virtual int GetMapScore(void * reference);   // each map might count with a different score system or have none at all
												// example: Haunted Mines -> Team skulls
												// example: battlefield of eternity -> ?  inmortal health?

}MapClass, * Map;



typedef class _StructureClass 
{
protected:
	MapPosition position;
	StructureType type;
	HealthBar health;   // includes hp + armor
	virtual int InitStructure(); // depends on the child/type of structure


	int GetArmor(int * armor_ref);  // get present armor from health
	int ModifyArmor(int amount);
	int TakeDamage(int damage);   // go directly to health_bar

} StructureClass,*Structure;


class TowerStructure : public StructureClass
{
protected:
	int radius;
	
	int attackDamage;  // should this be a AA dmg class/struct
	double attackSpeed;

	int InitStructure()
	{
		type = Tower;
		radius = 5;
		attackDamage = 150;     // buildings don´t scale... but it might be better to read these attributes directly from file.
		// ...
		return 1;
	};

	// Constructor initializes class pre-defined values
	TowerStructure() {
		InitStructure();
	};
};

#endif // _MAP_H_