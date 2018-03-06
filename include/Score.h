/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Score.h'			DESCRIPTION:
	
Storage of game event functions.

Ex: death count, objective tracking, forts, ...

-----------------------------------------------------------------------------*/


#ifndef _SCORE_H_
#define _SCORE_H_


#include "du.h"

extern enum GameType; // defined in Game.h

typedef class ScoreClass {
public:
	ScoreClass();
	~ScoreClass();
protected:

	virtual struct ScoreValue {};  // has to be defined for each child
	virtual int updateScore();
	virtual int createScore();
	Team * TeamA;
	Team * TeamB;


}*Score;

typedef class GameScoreClass : ScoreClass
{

public:
	GameScoreClass();
	~GameScoreClass();

protected:
	GameType type;
	int declareWinner();
	int scorePoint();
	Team* TeamA;
	Team* TeamB;
private:

}*GameScore;





#endif // _SCORE_H_