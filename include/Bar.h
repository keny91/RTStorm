#pragma once
class Bar
{
private:
	int current_value;
	int max_value;
	bool inmune;
	


public:
	Bars();
	~Bars();
	int takeDamage(int damage_per_tick, int nof_ticks);
	int takeDamage(int damage_per_tick); // polymorphism
	int healDamage();

};

