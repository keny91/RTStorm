#ifndef  __HERO_H__
#define  __HERO_H__

#include "Attributes.h"
#include "Talent.h"  // implements talent, talent_tier
#include "du.h"

// assume characters can have an X amount of tiers, each with a Variable amount of talents options

typedef class _HeroClass
{
protected:
	typedef enum _HeroStatus{normal, stuned, dazed, mind_controlled, unstopabble, stopped, untargetable, stasis, invulnerable, slowed, ,???}status;
	Hero();
	~Hero();
	
	
	//Health current_health;
	
	// talents
	DuArray AvailibleTalents;  // DuArray/DuList of talent tiers
	DuArray ChosenTalents;  // Duarray of selected talents
	                        // grows with every selection on talent tier
	
	virtual int loadHero();  // defined for every Hero
	virtual int talentPicked(TalentTier theTier, Talent theTalent, int level);
	virtual int levelUp();
	
	Player ControlledBy(); // returns the player
		
private:
	
	
	
} HeroClass, * Hero;

#endif /* __Hero_H__ */
