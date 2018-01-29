#pragma once


#ifndef _MOD_H_
#define _MOD_H_



class Modifier
{
private:
	int current_value;
	int max_cap, min_cap;
	bool inmune;
	bool inverse_proportional;  // Armor is inverse_proportional: more means less output value
	


public:
	Modifier();
	~Modifier();
	int applyModifier(int value);
	int applyModifier(int value);

};


#endif // _ARMOR_H_