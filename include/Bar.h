#pragma once
#ifndef _BAR_H_
#define _BAR_H_
//#define 

#include "Armor.h"


class Bar
{
protected:
	int current_value;
	int max_value;
	bool inmune;
	bool checkEmpty();
	int modifyValue();
	


public:
	Bar();
	~Bar();
	void SetCallBack_On_Empty(void*);

};



class HealthBar : Bar 
{
private:
	Armor armor;


public:
	int takeDamage(int value);
	int takeDamage(int value, int nof_ticks);
	int healDamage(int value);
	int healDamage(int value, int nof_ticks);


};

#endif // _BAR_H_