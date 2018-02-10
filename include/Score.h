/*------------------RT ANALYSIS API FOR HEROES OF THE STORM ------------------


This program is meant to be run in the background while playing Heroes of the
Storm (All rights reserved by Activision Blizzard and Blizzard Entertainment).


		'Score.h'			DESCRIPTION:
	
Storage of game event functions.

Ex: death count, objective tracking, forts, ...

-----------------------------------------------------------------------------*/

#include "du.h"



#ifndef _SCORE_H_
#define _SCORE_H_

extern class Team;


class Score {
public:
	Score();
	~Score();
protected:

	virtual struct ScoreValue {};  // has to be defined for each child
	virtual int updateScore();
	virtual int createScore();
	Team * TeamA;
	Team * TeamB;


};

class GameScore : Score
{
	typedef int GameType;
public:
	GameScore();
	~GameScore();

protected:
	GameType type;
	int declareWinner();
	int scorePoint();
	Team* TeamA;
	Team* TeamB;
private:

};





#endif // _SCORE_H_