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
	TalentTree talentTree;  // DuArray/DuList of talent tiers
	Talent * pickedTalents;  // array of size nofTalentTiers that stores references to the picked talents.
	//DuArray ChosenTalents;  // Duarray of selected talents
	                        // grows with every selection on talent tier
	
	virtual int loadHero();  // defined for every Hero
	virtual int talentPicked(TalentTier theTier, Talent theTalent, int level);
	virtual int levelUp();  // calls to talent tree, 
	
	Player ControlledBy(); // returns the player
	int PickTalent(int theLevelTier, int indexTalent);  // finds a talent using the indexes
		
private:
	
	
	
} HeroClass, * Hero;



typedef struct _TalentTreeStruct
{
	private:
		DuArray theTalentTiers;  // list of tier structures
		int * tierLevels;  // array to store tier levels; by default
		
		int nofTalentTiers;
	
	public:
		int getNextTier(int * tier_Ref, int * tier_Level);
		int createDefaultTierLevels();
		int createTierLevels(int * tier_Levels, int nof_tiers);
	 // returns the index to the first tier that is ready to be picked; -1 otherwise
		int checkUnlockTier(int current_Level, int *First_Unlocked_Tier);
		Talent SelectTalent(int pick_index, TalentTier the_Tier);  // returns a reference to the talent
	
}TalentTreeStruct, *TalentTree;

typedef struct _TalentTierStruct
{
private:

	int unlockLevel;  
	int nof_choices;
	int indexTalentChoice;
	Talent talentPicked;
	bool locked;
	bool selected;
	
	
public:
	Talent SelectTalent(int pick_index);  // returns a reference to the talent
	int UnlockTier();	// changes internal 'locked' value
	
} TalentTierStruct, *TalentTier;



#endif /* __Hero_H__ */
