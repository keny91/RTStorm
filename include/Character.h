#pragma once

#include "Stats.h"
#include ""



class Character
{
public:
	Character();
	Stats character_stats;
	Health current_health;

	~Character();
};

